#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "common.hpp"

using Literal = std::variant<double, int, std::string, bool>;

class Token {
public:
    Token(TokenType type, std::string lexeme, std::optional<Literal> literal, int line);
    ~Token() = default;
    std::string to_string();
private:
    TokenType type;
    std::string lexeme;
    std::optional<Literal> literal;
    int line;
};

#endif
