#include "common.hpp"
#include "token.hpp"

std::unordered_map<TokenType, std::string> tokens_table = {
    {EOS, "EOS"},
    {PLUS, "Plus"},
    {SUB, "Sub"},
    {STAR, "Star"},
    {SLASH, "Slash"},
    {R_PAREN, "RParen"},
    {L_PAREN, "LParen"},
    {L_BRACKET, "LBracket"},
    {R_BRACKET, "RBracket"},
    {COMMA, "Comma"},
    {DOT, "Dot"},
    {NOT, "Not"},
    {EQUALS, "Equals"},
    {GREATER, "Greater"},
    {LESSER, "Lesser"},
    {GREATER_EQUALS, "GreaterEquals"},
    {LESSER_EQUALS, "LesserEquals"},
    {EQUALS_EQUALS, "EqualsEquals"},
    {NOT_EQUALS, "NotEquals"},
    {IDENTIFIER, "Identifier"},
    {VYTLAC, "Vytlac"},
    {NUMBER, "Number"},
    {STRING, "String"},
    {KED, "Ked"},
    {INAK, "Inak"},
    {INAK_KED, "InakKed"},
    {AK, "Ak"},
    {POKIAL, "Pokial"},
    {VRATIT, "Vratit"},
    {FUNK, "Funk"},
    {TRIEDA, "Trieda"}
};

std::unordered_map<std::string, TokenType> keywords_table = {
    {"vytlac", VYTLAC},
    {"ked", KED},
    {"inak", INAK},
    {"inaked", INAK_KED},
    {"ak", AK},
    {"pokial", POKIAL},
    {"vratit", VRATIT},
    {"funk", FUNK},
    {"trieda", TRIEDA}
};
