#ifndef TOKEN_H
#define TOKEN_H

#include "common.h"
#include <unordered_map>

typedef enum {
    // Single-character tokens.
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
    TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
    TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR,
    // One or two character tokens.
    TOKEN_BANG, TOKEN_BANG_EQUAL,
    TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
    TOKEN_GREATER, TOKEN_GREATER_EQUAL,
    TOKEN_LESS, TOKEN_LESS_EQUAL,
    // Literals.
    TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER,
    // Keywords.
    TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, TOKEN_FALSE,
    TOKEN_FOR, TOKEN_FUN, TOKEN_IF, TOKEN_NIL, TOKEN_OR,
    TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, TOKEN_THIS,
    TOKEN_TRUE, TOKEN_LET, TOKEN_WHILE,
    TOKEN_ERROR,
    TOKEN_EOF
}TokenType;

inline static std::unordered_map<TokenType, std::string> tokens_map = {
    {TOKEN_LEFT_PAREN, "LParen"}, 
    {TOKEN_RIGHT_PAREN, "RParen"},
    {TOKEN_LEFT_BRACE, "LBrace"}, 
    {TOKEN_RIGHT_BRACE, "RBrace"},
    {TOKEN_COMMA, "Comma"}, 
    {TOKEN_DOT, "Dot"}, 
    {TOKEN_MINUS, "Minus"},
    {TOKEN_PLUS, "Plus"}, 
    {TOKEN_STAR, "Star"}, 
    {TOKEN_SLASH, "Slash"},
    {TOKEN_SEMICOLON, "Semicolon"}, 
    {TOKEN_BANG, "Bang"},
    {TOKEN_BANG_EQUAL, "Bang_Equal"}, 
    {TOKEN_EQUAL, "Equal"},
    {TOKEN_EQUAL_EQUAL, "Equal_Equal"}, 
    {TOKEN_GREATER, "Greater"},
    {TOKEN_GREATER_EQUAL, "Greater_Equal"}, 
    {TOKEN_LESS, "Less"},
    {TOKEN_LESS_EQUAL, "Less_Equal"}, 
    {TOKEN_IDENTIFIER, "Identifier"},
    {TOKEN_STRING, "String"}, 
    {TOKEN_NUMBER, "Number"}, 
    {TOKEN_AND, "And"},
    {TOKEN_CLASS, "Class"}, 
    {TOKEN_ELSE, "Else"}, 
    {TOKEN_FALSE, "False"},
    {TOKEN_FOR, "For"}, 
    {TOKEN_FUN, "Fun"}, 
    {TOKEN_IF, "If"}, 
    {TOKEN_NIL, "Nil"},
    {TOKEN_OR, "Or"}, 
    {TOKEN_PRINT, "Print"}, 
    {TOKEN_RETURN, "Return"},
    {TOKEN_SUPER, "Super"}, 
    {TOKEN_THIS, "This"}, 
    {TOKEN_TRUE, "True"},
    {TOKEN_LET, "Let"}, 
    {TOKEN_WHILE, "While"}, 
    {TOKEN_ERROR, "Error"},
    {TOKEN_EOF, "EOF"}
};

inline static std::unordered_map<std::string, TokenType> keywords_map = {
    {"and", TOKEN_AND},
    {"class", TOKEN_CLASS}, 
    {"else", TOKEN_ELSE}, 
    {"false", TOKEN_FALSE},
    {"for", TOKEN_FOR}, 
    {"fun", TOKEN_FUN}, 
    {"if", TOKEN_IF}, 
    {"nil", TOKEN_NIL},
    {"or", TOKEN_OR}, 
    {"print", TOKEN_PRINT}, 
    {"return", TOKEN_RETURN},
    {"super", TOKEN_SUPER}, 
    {"this", TOKEN_THIS}, 
    {"true", TOKEN_TRUE},
    {"let", TOKEN_LET}, 
    {"while", TOKEN_WHILE} 
};

class Token {
public:
    Token(TokenType type, std::string lexeme, int line);
    ~Token() = default;
    std::string to_string();
public:
    TokenType type;
    std::string lexeme;
    int line;
};

#endif
