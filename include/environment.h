#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "runtime_error.h"

class Environment {
public:
    Environment() = default;
    ~Environment() = default;
    void define(Token name, LiteralValue value);
    void assign(Token name, LiteralValue value);
    LiteralValue get(Token name);
public:
    std::unordered_map<std::string, LiteralValue> values;
};

#endif
