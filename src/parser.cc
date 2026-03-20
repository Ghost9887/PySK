#include "parser.h"

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
    return std::make_shared<ExpressionStmnt>(expression());
}

std::shared_ptr<Expr> Parser::expression() {
    std::shared_ptr<Expr> expr = binary();
    consume(T_SEMICOLON, "Expected ';'.");
    return expr;
}

std::shared_ptr<Expr> Parser::binary() {
    std::shared_ptr<Expr> expr = primary();
    if (match(T_PLUS, T_MINUS, T_STAR, T_SLASH)) {
        Token op = tokens.at(ip - 1);
        std::shared_ptr<Expr> right = primary();
        return std::make_shared<BinaryExpr>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::primary() {
    if (match(T_NUMBER)) return std::make_shared<LiteralExpr>(tokens.at(ip - 1).literal);

    return nullptr;
}

TokenType Parser::peek_type() {
    return tokens.at(ip).type;
}

void Parser::advance() {
    ip++;
}

template<typename... TokenTypes>
bool Parser::match(TokenTypes... types) {
    if (is_at_end()) return false;
    for (TokenType type : {types...}) {
        if (peek_type() == type){ 
            advance();
            return true;
        }
    }

    return false;
}

void Parser::consume(TokenType type, std::string message) {
    if (peek_type() != type) return;
    advance();
}

bool Parser::is_at_end() {
    return ip >= tokens.size();
}
