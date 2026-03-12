#ifndef PARSER_H
#define PARSER_H

#include "common.h"
#include "expr.h"
#include "stmnt.h"
#include "dio.h"

class ParseError : public std::runtime_error {
public:
    ParseError() : std::runtime_error("Parse error") {}
};

class Parser {
public:
    Parser(std::vector<Token> tokens);
    ~Parser() = default;
    std::vector<std::shared_ptr<Stmnt>> parse();
private:
    std::vector<Token> tokens;
    int current;
private:
    std::shared_ptr<Stmnt> statement(); 
    std::shared_ptr<Stmnt> print_statement();
    std::shared_ptr<Stmnt> expression_statement();
    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> comparison();
    std::shared_ptr<Expr> term();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> unary();
    std::shared_ptr<Expr> primary();
    ParseError error(Token &token, std::string message);
    void synchronize();
    template<typename... TokenType>
    bool match(TokenType... types);
    bool check(TokenType type);
    Token &consume(TokenType type, std::string message);
    Token &peek();
    Token &previous();
    Token &advance();
    bool is_at_end();
};

#endif
