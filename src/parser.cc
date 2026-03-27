#include "parser.h"

//TODO: fix errors

Parser::Parser(std::vector<Token> tokens) :
    tokens(tokens), ip(0), had_error(false) {}

std::vector<std::shared_ptr<Stmnt>> Parser::parse() {
    std::vector<std::shared_ptr<Stmnt>> statements;
    while (!is_at_end()) {
        statements.push_back(statement());
    }
    return statements;
}

std::shared_ptr<Stmnt> Parser::statement() {
    if (match(T_VYTLAC)) return std::make_shared<PrintStmnt>(expression());
    return std::make_shared<ExpressionStmnt>(expression());
}

std::shared_ptr<Expr> Parser::expression() {
    std::shared_ptr<Expr> expr = binary();
    consume(T_SEMICOLON, "Ocakvany ';'.");
    return expr;
}

std::shared_ptr<Expr> Parser::binary() {
    return equality();
}

std::shared_ptr<Expr> Parser::equality() {
    std::shared_ptr<Expr> expr = comparison();

    if (match(T_BANG_EQUAL, T_EQUAL_EQUAL)) {
        Token op = tokens.at(ip - 1);
        std::shared_ptr<Expr> right = comparison();
        return std::make_shared<BinaryExpr>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::comparison() {
    std::shared_ptr<Expr> expr = additive();

    if (match(T_GREATER, T_GREATER_EQUAL, T_LESS, T_LESS_EQUAL)) {
        Token op = tokens.at(ip - 1);
        std::shared_ptr<Expr> right = additive();
        return std::make_shared<BinaryExpr>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::additive() {
    std::shared_ptr<Expr> expr = factor();

    if (match(T_PLUS, T_MINUS)) {
        Token op = tokens.at(ip - 1);
        std::shared_ptr<Expr> right = factor();
        return std::make_shared<BinaryExpr>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::factor() {
    std::shared_ptr<Expr> expr = unary();

    if (match(T_STAR, T_SLASH)) {
        Token op = tokens.at(ip - 1);
        std::shared_ptr<Expr> right = unary();
        return std::make_shared<BinaryExpr>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::unary() {
    if (match(T_MINUS, T_BANG)) {
        Token op = tokens.at(ip - 1);
        std::shared_ptr<Expr> right = unary();
        return std::make_shared<UnaryExpr>(op, right);
    }

    return primary();
}

std::shared_ptr<Expr> Parser::primary() {
    if (match(T_NUMBER)) return std::make_shared<LiteralExpr>(tokens.at(ip - 1).literal);

    if (match(T_LPAREN)) {
        std::shared_ptr<Expr> expr = binary();
        consume(T_RPAREN, "Ocakvany ')'.");
        return std::make_shared<GroupingExpr>(expr);
    }

    return nullptr;
}

TokenType Parser::peek_type() {
    return tokens.at(ip).type;
}

Token Parser::peek() {
    return tokens.at(ip);
}

void Parser::advance() {
    ip++;
}

template<typename... TokenTypes>
bool Parser::match(TokenTypes... types) {
    if (is_at_end()) error("Neocakvany koniec vyrazu.");
    for (TokenType type : {types...}) {
        if (peek_type() == type){ 
            advance();
            return true;
        }
    }

    return false;
}

void Parser::consume(TokenType type, std::string message) {
    if (is_at_end()) error(message); 
    else if (peek_type() != type) error(message);
    advance();
}

bool Parser::is_at_end() {
    return ip >= tokens.size();
}

void Parser::error(std::string message) {
    throw ParseError(message);
}
