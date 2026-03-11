#include "parser.h"

Parser::Parser(std::vector<Token> tokens) 
    : tokens(std::move(tokens)), current(0) {}

std::shared_ptr<Expr> Parser::parse() {
    try {
        return expression();
    }catch (ParseError error) {
        return NULL;
    }
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
    return equality();
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
