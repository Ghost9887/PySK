#ifndef TOKEN_H
#define TOKEN_H

#include <ostream>
#include <unordered_map>
#include <iostream>
#include <string>
#include <variant>
#include "values.h"

typedef enum {
    T_PLUS, T_MINUS, T_STAR, T_SLASH,
    T_EQUAL, T_DOT, T_COMMA, T_GREATER,
    T_LESS, T_BANG, T_RPAREN, T_LPAREN,
    T_RBRACE, T_LBRACE, T_SEMICOLON,

    T_EQUAL_EQUAL, T_GREATER_EQUAL, T_LESS_EQUAL,
    T_BANG_EQUAL, T_NUMBER, T_STRING, T_IDENTIFIER,

    T_LET, T_A, T_ALEBO, T_AK, T_INAK, T_POKIAL,
    T_PRE, T_SLUCKA, T_TRIEDA, T_FUNK, T_VRATIT,
    T_VYTLAC, T_PRAVDA, T_NEPRAVDA
}TokenType;

inline static const std::unordered_map<TokenType, std::string> tokens_map = {
    {T_PLUS, "Plus"},
    {T_MINUS, "Minus"},
    {T_STAR, "Star"},
    {T_SLASH, "Slash"},
    {T_EQUAL, "Equal"},
    {T_DOT, "Dot"},
    {T_COMMA, "Comma"},
    {T_GREATER, "Greater"},
    {T_LESS, "Less"},
    {T_BANG, "Bang"},
    {T_RPAREN, "RParen"},
    {T_LPAREN, "LParen"},
    {T_RBRACE, "RBrace"},
    {T_LBRACE, "LBrace"},
    {T_SEMICOLON, "Semicolon"},
    {T_EQUAL_EQUAL, "Equal_Equal"},
    {T_GREATER_EQUAL, "Greater_Equal"},
    {T_LESS_EQUAL, "Less_Equal"},
    {T_BANG_EQUAL, "Bang_Equal"},
    {T_NUMBER, "Number"},
    {T_STRING, "String"},
    {T_IDENTIFIER, "Identifier"},
    {T_LET, "Let"},
    {T_A, "A"},
    {T_ALEBO, "Alebo"},
    {T_AK, "Ak"},
    {T_INAK, "Inak"},
    {T_POKIAL, "Pokial"},
    {T_PRE, "Pre"},
    {T_SLUCKA, "Slucka"},
    {T_TRIEDA, "Trieda"},
    {T_FUNK, "Funk"},
    {T_VRATIT, "Vratit"},
    {T_VYTLAC, "Vytlac"},
    {T_PRAVDA, "Pravda"},
    {T_NEPRAVDA, "Nepravda"},
};

inline static const std::unordered_map<std::string, TokenType> keywords_map = {
    {"let", T_LET},
    {"aa", T_A},
    {"ak", T_AK},
    {"alebo", T_ALEBO},
    {"inak", T_INAK},
    {"pokial", T_POKIAL},
    {"pre", T_PRE},
    {"slucka", T_SLUCKA},
    {"trieda", T_TRIEDA},
    {"funk", T_FUNK},
    {"vratit", T_VRATIT},
    {"vytlac", T_VYTLAC},
    {"pravda", T_PRAVDA},
    {"nepravda", T_NEPRAVDA},
};

using LiteralValue = std::variant<std::monostate, Value, std::string, bool>;

class Token {
public:
    Token(TokenType type, std::string lexeme, int line, LiteralValue literal);
    ~Token() = default;
    std::string to_string();
    static std::string literal_to_string(LiteralValue literal);
public:
    TokenType type;
    std::string lexeme;
    int line;
    LiteralValue literal;
    bool operator==(const Token& other) const {
        return type == other.type &&
               lexeme == other.lexeme &&
               line == other.line;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Token& t) {
    os << "Token("
       << "type=" << t.type << ", "
       << "lexeme=\"" << t.lexeme << "\", "
       << "line=" << t.line
       << ")";
    return os;
}

#endif
