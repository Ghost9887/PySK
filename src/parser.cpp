#include "parser.h"

Parser::Parser(std::vector<Token> tokens) 
    : tokens(std::move(tokens)), current(0) {}

std::vector<std::shared_ptr<Stmnt>> Parser::parse() {
    std::vector<std::shared_ptr<Stmnt>> statements;

    while (!is_at_end()) {
        statements.push_back(declaration());
    }
    return statements;
}

Token &Parser::consume(TokenType type, std::string message) {
    if (check(type)) return advance();

    throw error(peek(), message);
}

void Parser::synchronize() {
    advance();

    while (!is_at_end()) {
        if (previous().type == TokenType::SEMICOLON) return;

        switch (peek().type) {
            case TokenType::TRIEDA:
            case TokenType::FUNK:
            case TokenType::LET:
            case TokenType::PRE:
            case TokenType::AK:
            case TokenType::POKIAL:
            case TokenType::VYTLAC:
            case TokenType::VRATIT:
                return;
        }

        advance();
    }
}

ParseError Parser::error(Token &token, std::string message) {
    Dio::error(token, message);
    return ParseError();
}

std::shared_ptr<Stmnt> Parser::declaration() {
    try {
        if (match(TokenType::LET)) return let_declaration();
        return statement();
    }catch (ParseError error) {
        std::cout << "error" << '\n';
        synchronize();
        return nullptr;
    }
}

std::shared_ptr<Stmnt> Parser::let_declaration() {
    Token name = consume(TokenType::IDENTIFIER, "Ocakavany nazov premeny");

    std::shared_ptr<Expr> initializer = nullptr;
    if (match(TokenType::EQUAL)) initializer = expression();

    consume(TokenType::SEMICOLON, "Ocakavany ';' za vyrazom");
    return std::make_shared<Let>(name, initializer);
}

std::shared_ptr<Stmnt> Parser::statement() {
    if (match(TokenType::AK)) return if_statement();
    if (match(TokenType::VYTLAC)) return print_statement();
    if (match(TokenType::L_BRACE)) return std::make_shared<Block>(block());

    return expression_statement();
}

std::shared_ptr<Stmnt> Parser::if_statement(){
    consume(TokenType::L_PAREN, "Ocakavany '(' za 'ked'.");
    std::shared_ptr<Expr> condition = expression();
    consume(TokenType::R_PAREN, "Ocakavany ')' na konci 'ked'.");

    std::shared_ptr<Stmnt> then_branch = statement();
    std::optional<std::shared_ptr<Stmnt>> else_branch = std::nullopt;
    if (match(TokenType::INAK)) {
        else_branch = statement();
    }

    return std::make_shared<If>(condition, then_branch, else_branch);
}

std::shared_ptr<Stmnt> Parser::print_statement() {
    std::shared_ptr<Expr> expr = expression();
    consume(TokenType::SEMICOLON, "Ocakavany ';' za vyrazom.");

    return std::make_shared<Print>(expr);
}

std::vector<std::shared_ptr<Stmnt>> Parser::block() {
    std::vector<std::shared_ptr<Stmnt>> statements;

    while (!check(TokenType::R_BRACE) && !is_at_end()) {
        statements.push_back(declaration());
    }

    consume(TokenType::R_BRACE, "Ocakavany '}' za blokom");
    return statements;
}

std::shared_ptr<Stmnt> Parser::expression_statement() {
    std::shared_ptr<Expr> expr = expression();
    consume(TokenType::SEMICOLON, "Ocakavany ';' za vyrazom.");

    return std::make_shared<Expression>(expr);
}

std::shared_ptr<Expr> Parser::assignment() {
    std::shared_ptr<Expr> expr = equality();
    if (match(TokenType::EQUAL)) {
        Token equals = previous();
        std::shared_ptr<Expr> value = assignment();

        auto var = std::dynamic_pointer_cast<Variable>(expr);
        if (var) {
            return std::make_shared<Assign>(var->name, value);
        }

        error(equals, "Nelegalny zadany ciel.");
    }

    return expr;
}

std::shared_ptr<Expr> Parser::comparison() {
    std::shared_ptr<Expr> expr = term();

    while (match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESSER, TokenType::LESSER_EQUAL)) {
        Token &op = previous();
        std::shared_ptr<Expr> right = term();
        expr = std::make_shared<Binary>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::primary() {
    if (match(TokenType::NEPRAVDA)) return std::make_shared<Literal>(false);
    if (match(TokenType::PRAVDA)) return std::make_shared<Literal>(true);
    if (match(TokenType::NIC)) return std::make_shared<Literal>(std::monostate());

    if (match(TokenType::NUMBER, TokenType::STRING)) {
        return std::make_shared<Literal>(previous().literal);
    }

    if (match(TokenType::IDENTIFIER)) return std::make_shared<Variable>(previous());

    if (match(TokenType::L_PAREN)) {
        std::shared_ptr<Expr> expr = expression();
        consume(TokenType::R_PAREN, "Ocakavany ')' za vyrazom.");
        return std::make_shared<Grouping>(expr);
    }

    throw error(peek(), "Ocakavany vyraz.");
}

std::shared_ptr<Expr> Parser::unary() {
    if (match(TokenType::BANG, TokenType::MINUS)) {
        Token &op = previous();
        std::shared_ptr<Expr> right = unary();
        return std::make_shared<Unary>(op, right);
    }

    return primary();
}

std::shared_ptr<Expr> Parser::factor() {
    std::shared_ptr<Expr> expr = unary();

    while (match(TokenType::STAR, TokenType::SLASH, TokenType::PERCENT)) {
        Token &op = previous();
        std::shared_ptr<Expr> right = unary();
        expr = std::make_shared<Binary>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::term() {
    std::shared_ptr<Expr> expr = factor();

    while (match(TokenType::MINUS, TokenType::PLUS)) {
        Token &op = previous();
        std::shared_ptr<Expr> right = factor();
        expr = std::make_shared<Binary>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::equality() {
    std::shared_ptr<Expr> expr = comparison();

    while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
        Token &op = previous();
        std::shared_ptr<Expr> right = comparison();
        expr = std::make_shared<Binary>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::expression() {
    return assignment();
}

template<typename... T>
bool Parser::match(T... types) {
    for (TokenType t : {types...}) {
        if (check(t)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type) {
    if (is_at_end()) return false;
    return peek().type == type;
}

Token &Parser::advance() {
    if (!is_at_end()) current++;
    return previous();
}

bool Parser::is_at_end() {
    return peek().type == TokenType::_EOF;
}

Token &Parser::previous() {
    return tokens.at(current - 1);
}

Token &Parser::peek() {
    return tokens.at(current);
}
