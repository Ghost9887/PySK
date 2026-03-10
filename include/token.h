#ifndef TOKEN_H
#define TOKEN_H

#include "common.h"

using Literal = std::variant<std::monostate, int, double, std::string, bool>;

class Token {
public:
    Token(TokenType type, std::string lexeme, Literal literal, int line, int column);
    ~Token() = default;
    std::string to_string();
private:
    TokenType type;
    std::string lexeme;
    Literal literal;
    int line;
    int column;
};

#endif
