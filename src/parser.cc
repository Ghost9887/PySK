#include "parser.h"

Parser::Parser(std::vector<Token> tokens) :
    tokens(tokens), ip(0) {}

std::shared_ptr<Stmnt> Parser::parse() {
    std::shared_ptr<Stmnt> stmnt = expression();
    return stmnt;
}

std::shared_ptr<Stmnt> Parser::expression() {
    if (match(T_LET)) return let_statement();

    return std::make_shared<ExpressionStmnt>(binary());
}

std::shared_ptr<Stmnt> Parser::let_statement() {
    return nullptr;
} 

std::shared_ptr<Expr> Parser::binary() {
    std::shared_ptr<Expr> expr = assignment();
    consume(T_SEMICOLON, "Expected semicolon.");
    return expr;
}

std::shared_ptr<Expr> Parser::unary() {
    std::shared_ptr<Expr> expr = primary();

    if (match(T_MINUS)) {
        Token op = tokens.at(ip - 1);
        std::shared_ptr<Expr> value = assignment();
        return std::make_shared<UnaryExpr>(op, value);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::factor() {
    std::shared_ptr<Expr> expr = unary();

    if (match(T_STAR, T_SLASH)) {
        Token op = tokens.at(ip - 1);
        std::shared_ptr<Expr> right = assignment();
        return std::make_shared<FactorExpr>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::additive() {
    std::shared_ptr<Expr> expr = factor();

    if (match(T_PLUS, T_MINUS)) {
        Token op = tokens.at(ip - 1);
        std::shared_ptr<Expr> right = assignment();
        return std::make_shared<AdditiveExpr>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::equality() {
    std::shared_ptr<Expr> expr = additive();

    if (match(T_EQUAL_EQUAL, T_BANG_EQUAL, T_GREATER, T_LESS, T_GREATER_EQUAL, T_LESS_EQUAL)) {
        Token op = tokens.at(ip - 1);
        std::shared_ptr<Expr> right = assignment();
        return std::make_shared<EqualityExpr>(expr, op, right); 
    }

    return expr;
}

std::shared_ptr<Expr> Parser::conditional() {
    std::shared_ptr<Expr> expr = equality();

    if (match(T_A, T_ALEBO)) {
        Token op = tokens.at(ip - 1);
        std::shared_ptr<Expr> right = assignment();
        return std::make_shared<ConditionalExpr>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::assignment() {
    /*
    if (peek_next(T_EQUAL)) {
        std::cout << "assignemnt" << '\n';
    };
    */

    return conditional();
}

std::shared_ptr<Expr> Parser::primary() {
    if (match(T_NUMBER)) {
        return std::make_shared<ValueExpr>(tokens.at(ip - 1).lexeme);
    }

    return nullptr;
}

template<typename... TokenTypes>
bool Parser::match(TokenTypes... types) {
    if (is_at_end()) return false;

    for (TokenType type : {types...}) {
        if (tokens.at(ip).type == type) {
            ip++;
            return true;
        }
    }
    return false;
}

void Parser::consume(TokenType expected, std::string message) {
    if (is_at_end()) {
        error(message, tokens.at(ip - 1));
        return;
    }
    else if (tokens.at(ip).type == expected) {
        ip++;
        return;
    }
    error(message, tokens.at(ip));
}

bool Parser::is_at_end() {
    return ip >= tokens.size();
}

void Parser::error(const std::string message, Token &token) {
    std::string error_message = "Parse Error: " + message + " at: " + std::to_string(token.line);
    throw ParseError(error_message);
}
