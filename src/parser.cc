#include "parser.h"

Parser::Parser(std::vector<Token> tokens) :
    tokens(tokens), ip(0), had_error(false) {}

std::vector<std::shared_ptr<Stmnt>> Parser::parse() {
    std::vector<std::shared_ptr<Stmnt>> statements;
    /*
    while (!is_at_end()) {
        statements.push_back(statement());
    }
    */
    return statements;
}

std::shared_ptr<Stmnt> Parser::statement() {
    return std::make_shared<ExpressionStmnt>(expression());
}

std::shared_ptr<Expr> Parser::expression() {
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
    for (TokenType type : {types...}) {
        if (peek_type() == type){ 
            advance();
            return true;
        }
    }

    return false;
}

void Parser::consume(TokenType type) {
    if (peek_type() != type) return;
    advance();
}

bool Parser::is_at_end() {
    return ip >= tokens.size();
}
