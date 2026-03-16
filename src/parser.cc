#include "parser.h"

Parser::Parser(std::vector<Token> tokens) :
    tokens(tokens) {}

void Parser::parse() {
    //TODO: IMPLEMENT
}

void Parser::error(const std::string message, Token &token) {
    std::string error_message = "Parse Error: " + message + " at: " + std::to_string(token.line);
    throw ParseError(error_message);
}
