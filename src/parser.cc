#include "parser.h"

Parser::Parser(std::vector<Token> tokens) :
    tokens(tokens), ip(0) {}

std::shared_ptr<Stmnt> Parser::parse() {
    std::shared_ptr<Stmnt> stmnt = expression();
    return stmnt;
}

std::shared_ptr<Stmnt> Parser::expression() {
    return std::make_shared<ExpressionStmnt>(binary());
}

std::shared_ptr<Expr> Parser::binary() {
    std::shared_ptr<Expr> right = value();
    Token op = tokens.at(ip);   
    ip++;
    std::shared_ptr<Expr> left = value();
    return std::make_shared<BinaryExpr>(right, op, left);
}

std::shared_ptr<Expr> Parser::value() {
    if (match(T_NUMBER)) {
        return std::make_shared<ValueExpr>(tokens.at(ip - 1).lexeme);
    }
    error("Expected number or string", tokens.at(ip));
    return nullptr;
}

template<typename... TokenTypes>
bool Parser::match(TokenTypes... types) {
    for (TokenType type : {types...}) {
        if (tokens.at(ip).type == type) {
            ip++;
            return true;
        }
    }
    return false;
}

void Parser::consume(TokenType expected, std::string message) {
    if (tokens.at(ip).type == expected) {
        ip++;
        return;
    }
    error(message, tokens.at(ip));
}

void Parser::error(const std::string message, Token &token) {
    std::string error_message = "Parse Error: " + message + " at: " + std::to_string(token.line);
    throw ParseError(error_message);
}
