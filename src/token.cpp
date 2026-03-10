#include "token.h"

Token::Token(TokenType type, std::string lexeme, LiteralValue literal, int line, int column) :
    type(type), lexeme(lexeme), literal(literal), line(line), column(column) {}

std::string Token::to_string() {
    return "[" + tokens_map.at(type) + ", " + lexeme + ", " + std::to_string(line) + ", " + std::to_string(column) + "]";  
}
