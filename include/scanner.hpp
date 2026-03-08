#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "common.hpp"

class Scanner {
public:
    Scanner();
    ~Scanner() = default;
    void load(const char *file_name);
    void tokenize();
    void print_tokens();
private:
    std::vector<Token> tokens;
    std::string content;
    int ip;
    void advance();
    void add_token(Token token, std::string value);
    void add_token(Token token, int value);
    void add_token(Token token);
    bool is_at_end();
};

#endif
