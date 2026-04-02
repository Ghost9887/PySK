#include "token.h"
#include "debugger.h"

Token::Token(TokenType type, std::string lexeme, int line, LiteralValue literal) :
    type(type), lexeme(lexeme), line(line), literal(literal) {}

std::string Token::to_string() {
    return "[" + tokens_map.at(type) + ", " + lexeme + ", " + std::to_string(line) + ", " + Debugger::literal_to_string(literal) + "]";  
}

