#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "token.h"
#include "parse_error.h"

class Parser {
public:
    Parser(std::vector<Token>);
    ~Parser() = default;
    void parse();
private:
    void error(const std::string message, Token &token);
private:
    std::vector<Token> tokens;
    int ip;
};

#endif
