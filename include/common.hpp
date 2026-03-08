#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <unordered_map>

typedef enum { 
    EOS, Add, Sub, Multiply, Divide, 
    RParen, LParen, RBracket, LBracket, 
    Comma, Equals, Greater, Lesser, Dot,

    GreaterEquals, LesserEquals, GreaterLesser, 
    LesserGreater, EqualsEquals, 
    
    Identifier, Vytlac, Number, Ked, Inak, 
    InakKed, Ak, Pokial, Vratit, Funk 
}Token;

extern std::unordered_map<Token, std::string> lookup_table;

#endif
