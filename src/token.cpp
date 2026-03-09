#include "token.hpp"

Token::Token(TokenType type, std::string lexeme, std::optional<Literal> literal, int line) : 
    type(type), 
    lexeme(lexeme),
    literal(literal), 
    line(line) {}

void Token::print() {
    if (literal.has_value()) {
        std::cout 
            << "[" 
            << tokens_table.at(type) 
            << ", " 
            << lexeme 
            << ", " 
            << std::to_string(line) 
            << "]";
    }else {
        std::cout << "[" << tokens_table.at(type) << ", " << std::to_string(line) << "]";
    }
}
