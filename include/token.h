#ifndef TOKEN_H
#define TOKEN_H

#include <unordered_map>
#include <variant>
#include <memory>
#include <string>

typedef enum {
    L_PAREN, R_PAREN, L_BRACE, R_BRACE, COMMA,
    DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR, PERCENT,

    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESSER, LESSER_EQUAL,

    IDENTIFIER, STRING, NUMBER,

    A, TRIEDA, INAK, NEPRAVDA, FUNK, PRE, AK, NIC, ALEBO, 
    VYTLAC, VRATIT, SUPER, TOTO, PRAVDA, LET, POKIAL,

    _EOF
}TokenType;

inline static std::unordered_map<TokenType, std::string> tokens_map = {
    {L_PAREN, "LParen"},
    {R_PAREN, "RParen"},
    {L_BRACE, "LBrace"},
    {R_BRACE, "RBrace"},
    {COMMA, "Comma"},
    {DOT, "Dot"},
    {MINUS, "Minus"},
    {PLUS, "Plus"},
    {PERCENT, "Percent"},
    {SEMICOLON, "Semicolon"},
    {SLASH, "Slash"},
    {STAR, "Star"},
    {BANG, "Bang"},
    {BANG_EQUAL, "BangEqual"},
    {EQUAL, "Equal"},
    {EQUAL_EQUAL, "EqualEqual"},
    {GREATER, "Greater"},
    {GREATER_EQUAL, "GreaterEqual"},
    {LESSER, "Lesser"},
    {LESSER_EQUAL, "LesserEqual"},
    {IDENTIFIER, "Identifier"},
    {STRING, "String"},
    {NUMBER, "Number"},
    {A, "AA"},
    {TRIEDA, "Trieda"},
    {INAK, "Inak"},
    {NEPRAVDA, "Nepravda"},
    {FUNK, "Funk"},
    {PRE, "Pre"},
    {AK, "Ak"},
    {NIC, "Nic"},
    {ALEBO, "Alebo"},
    {VYTLAC, "Vytlac"},
    {VRATIT, "Vratit"},
    {SUPER, "Super"},
    {TOTO, "Toto"},
    {PRAVDA, "Pravda"},
    {LET, "Let"},
    {POKIAL, "Pokial"},
    {_EOF, "Eof"}
};

inline static std::unordered_map<std::string, TokenType> keywords_map = {
    {"aa", A},
    {"trieda", TRIEDA},
    {"inak", INAK},
    {"nepravda", NEPRAVDA},
    {"funk", FUNK},
    {"pre", PRE},
    {"ak", AK},
    {"nic", NIC},
    {"alebo", ALEBO},
    {"vytlac", VYTLAC},
    {"vratit", VRATIT},
    {"super", SUPER},
    {"toto", TOTO},
    {"pravda", PRAVDA},
    {"let", LET},
    {"pokial", POKIAL}
};

class DioCallable;
using LiteralValue = std::variant<std::monostate, double, int, std::string, bool, std::shared_ptr<DioCallable>>;

class Token {
public:
    Token(TokenType type, std::string lexeme, LiteralValue literal, int line, int column);
    ~Token() = default;
    std::string to_string();
    TokenType type;
    std::string lexeme;
    LiteralValue literal;
    int line;
    int column;
};

#endif
