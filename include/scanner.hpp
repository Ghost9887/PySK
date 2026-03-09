#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "common.hpp"
#include "token.hpp"

class Scanner {
public:
    Scanner();
    Scanner(std::string content);
    ~Scanner() = default;
    void load(const char *file_name);
    void tokenize();
    void print_tokens();
private:
    std::vector<Token> tokens;
    std::string content;
    int ip;
    int line;
    void advance();
    std::optional<char> peek();
    std::optional<char> peek_next();
    bool expected_next(char c);
    bool is_at_end();
    bool is_number(char c);
    bool is_alphanumeric(char c);
    void parse_number();
    void parse_identifier();
    void add_token(TokenType type);
    void add_token(TokenType type, int value); 
    void add_token(TokenType type, std::string value);
};

#endif
