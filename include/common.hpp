#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <optional>
#include <unordered_map>
#include <variant>

typedef enum {
    EOS, PLUS, SUB, STAR, SLASH, 
    R_PAREN, L_PAREN, R_BRACKET, L_BRACKET, 
    COMMA, EQUALS, GREATER, LESSER, DOT, NOT,

    GREATER_EQUALS, LESSER_EQUALS, EQUALS_EQUALS,
    NOT_EQUALS,

    IDENTIFIER, NUMBER, STRING, VYTLAC, KED, INAK, 
    INAK_KED, AK, POKIAL, VRATIT,  FUNK,
    TRIEDA
}TokenType;

extern std::unordered_map<TokenType, std::string> tokens_table;
extern std::unordered_map<std::string, TokenType> keywords_table;

#endif
