#ifndef SCANNER_H
#define SCANNER_H

#include "common.h"
#include "token.h"
#include "dio.h"

class Scanner {
public:
    Scanner(std::string content);
    ~Scanner() = default;
    std::vector<Token> scan_tokens();
private:
    bool is_at_end();
    void scan_token();
    char advance();
    void add_token(TokenType type);
    void add_token(TokenType type, LiteralValue literal);
    bool match(const char c);
    char peek();
    char peek_next();
    void string();
    bool is_digit(const char c);
    bool is_alpha(const char c);
    bool is_alphanumeric(const char c);
    void number();
    void identifier();
    std::string content;
    std::vector<Token> tokens;
    int start;
    int current;
    int line;
};

#endif
