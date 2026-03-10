#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <optional>
#include <unordered_map>
#include <variant>

typedef enum {
    L_PAREN, R_PAREN, L_BRACE, R_BRACE, COMMA,
    DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESSER, LESSER_EQUAL,

    IDENTIFIER, STRING, NUMBER,

    A, TRIEDA, INAK, NEPRAVDA, FUNK, PRE, AK, NIC, ALEBO, 
    VYTLAC, VRATIT, SUPER, TOTO, PRAVDA, LET, POKIAL,

    _EOF
}TokenType;

extern std::unordered_map<TokenType, std::string> tokens_map;
extern std::unordered_map<std::string, TokenType> keywords_map;

#endif
