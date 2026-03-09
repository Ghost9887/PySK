#include "parser.hpp"

Parser::Parser(std::vector<Token> &tokens) : tokens(tokens), current(0) {}

Token &Parser::peek() {
    return tokens.at(current);
}

void Parser::advance() {
    current++;
}

void Parser::parse() {
    while (current < tokens.size()) {
        break;
    }
}
