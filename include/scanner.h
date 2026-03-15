#ifndef SCANNER_H
#define SCANNER_H

#include "common.h"
#include "token.h"

class Scanner {
public:
    Scanner(const std::string source);
    ~Scanner() = default;
    Token scan_token();
private:
    bool is_at_end();
    bool is_alpha(char c);
    bool is_digit(char c);
    Token make_token(TokenType type);
    Token error_token(std::string message); 
    char advance();
    bool match(char expected);
    char peek();
    char peek_next();
    void skip_whitespace();
    Token string();
    Token number();
    Token identifier();
    TokenType identifier_type();
private:
    std::string source;
    int start;
    int current;
    int line;
};

#endif
