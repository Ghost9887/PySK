#ifndef PARSER_HPP
#define PARSER_HPP

#include "common.hpp"
#include "scanner.hpp"

class Parser {
public:
    Parser(std::vector<Token> &tokens);
    ~Parser() = default;
    void parse();
private:
    std::vector<Token> &tokens;
    int current;
    Token &peek();
    void advance();
};

#endif
