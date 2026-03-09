#include "token.hpp"

Token::Token(TokenType type, std::string lexeme, std::optional<Literal> literal, int line) : 
    type(type), 
    lexeme(lexeme),
    literal(literal), 
    line(line) {}

std::string Token::to_string() {
    if (literal.has_value()) {
        return 
            "[" 
            + tokens_table.at(type) 
            + ", " 
            + lexeme 
            + ", " 
            + std::to_string(line) 
            + "]";
    }else {
        return "[" + tokens_table.at(type) + ", " + std::to_string(line) + "]";
    }
}
