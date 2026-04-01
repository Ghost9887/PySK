#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "token.h"
#include "stmnt.h"
#include "parse_error.h"

class Parser {
public:
    Parser(std::vector<Token> tokens);
    ~Parser() = default;
    std::vector<std::shared_ptr<Stmnt>> parse();
private:
    std::shared_ptr<Stmnt> statement();
    std::shared_ptr<Stmnt> print_stmnt();
    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> binary();
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> comparison(); 
    std::shared_ptr<Expr> additive();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> unary();
    std::shared_ptr<Expr> primary();
    TokenType peek_type();
    Token peek();
    template<typename... TokenTypes>
    bool match(TokenTypes... types);
    void advance();
    void consume(TokenType type, std::string message);
    bool is_at_end();
    void error(const std::string message);
private:
    std::vector<Token> tokens;
    int ip;
    bool had_error;
};

#endif
