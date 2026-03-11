#ifndef TOKEN_H
#define TOKEN_H

#include "common.h"

using LiteralValue = std::variant<std::monostate, double, std::string, bool>;

class Token {
public:
    Token(TokenType type, std::string lexeme, LiteralValue literal, int line, int column);
    ~Token() = default;
    std::string to_string();
    TokenType type;
    std::string lexeme;
    LiteralValue literal;
    int line;
    int column;
};

#endif
