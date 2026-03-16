#ifndef SCANNER_H
#define SCANNER_H

#include <vector>
#include <string>
#include "token.h"

class Scanner {
public:
    Scanner(const std::string source);
    ~Scanner() = default;
    std::vector<Token> tokenize();
private:
    void make_token(TokenType type);
    bool is_alpha_numeric(char c);
    bool is_alpha(char c);
    void identifier();
    void string();
    void number();
    bool is_digit(char c);
    void advance();
    char peek(); 
    char peek_next();
    bool match(char c);
    bool is_at_end();
private:
    std::string source;
    int start;
    int current;
    int line;
    std::vector<Token> tokens;
};

#endif
