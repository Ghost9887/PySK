#ifndef COMPILER_H
#define COMPILER_H

#include <vector>
#include "stmnt.h"

class Compiler {
public:
    void compile(std::vector<std::shared_ptr<Stmnt>> statements);
public:
};

#endif
