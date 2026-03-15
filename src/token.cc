#include "token.h"

Token::Token(TokenType type, std::string lexeme, int line) :
type(type), lexeme(lexeme), line(line) {}

std::string Token::to_string() {
    return "[ " + tokens_map.at(type) + ", " + lexeme + ", " + std::to_string(line) + " ]";
}
