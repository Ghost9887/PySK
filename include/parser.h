#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "token.h"
#include "stmnt.h"

class Parser {
public:
    Parser(std::vector<Token> tokens);
    ~Parser() = default;
    std::vector<std::shared_ptr<Stmnt>> parse();
private:
    std::shared_ptr<Stmnt> statement();
    std::shared_ptr<Expr> expression();
    TokenType peek_type();
    void advance(); 
    template<typename... TokenTypes>
    bool match(TokenTypes... types);
    void consume(TokenType type);
    bool is_at_end();
private:
    std::vector<Token> tokens;
    int ip;
    bool had_error;
};

#endif
