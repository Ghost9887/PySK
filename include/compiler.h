#ifndef COMPILER_H
#define COMPILER_H

#include "stmnt.h"

class Compiler {
public:
    Compiler(std::shared_ptr<Stmnt> statement); 
    ~Compiler() = default;
    void compile();
public:
    std::shared_ptr<Stmnt> statement;
};

#endif
