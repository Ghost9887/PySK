#ifndef PARSER_H
#define PARSER_H

#include "common.h"
#include "token.h"

class Parser {
public:
    Parser();
    ~Parser() = default;
public:
    std::optional<Token> current;
    std::optional<Token> previous;
    bool had_error = false;
    bool panic_mode = false;
};

#endif
