#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include "token.h"
#include "parse_error.h"
#include "stmnt.h"

class Parser {
public:
    Parser(std::vector<Token> tokens);
    ~Parser() = default;
    std::shared_ptr<Stmnt> parse();
private:
    std::shared_ptr<Stmnt> expression();
    std::shared_ptr<Stmnt> let_statement();
    std::shared_ptr<Expr> binary();
    std::shared_ptr<Expr> primary();   
    std::shared_ptr<Expr> unary();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> additive();
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> conditional();
    std::shared_ptr<Expr> assignment();
    void error(const std::string message, Token &token);
    template<typename... TokenTypes>
    bool match(TokenTypes... types);
    bool is_at_end();
    void consume(TokenType expected, std::string message);
private:
    std::vector<Token> tokens;
    int ip;
};

#endif
