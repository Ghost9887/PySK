#include "token.h"

Token::Token(TokenType type, std::string lexeme, int line, LiteralValue literal) :
    type(type), lexeme(lexeme), line(line), literal(literal) {}

std::string Token::to_string() {
    return "[" + tokens_map.at(type) + ", " + lexeme + ", " + std::to_string(line) + "]";  
}

std::string Token::literal_to_string(LiteralValue literal) {
    return std::visit([](auto &&arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::string>) {
            return arg;
        } else if constexpr (std::is_arithmetic_v<T>) {
            return std::to_string(arg);
        } else if constexpr (std::is_same_v<T, bool>) {
            return arg ? "pravda" : "nepravda";
        } else {
            return "nic";
        }
    }, literal);
}
