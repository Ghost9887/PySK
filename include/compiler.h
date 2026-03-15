#ifndef COMPILER_H
#define COMPILER_H

#include "common.h"
#include "scanner.h"

class Compiler {
public:
    Compiler() = default;
    ~Compiler() = default;
    void compile(const std::string source);
};

#endif
