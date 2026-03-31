#ifndef PYSK_H
#define PYSK_H

#include <iostream>
#include "scanner.h"
#include "debugger.h"
#include "parser.h"
#include "compiler.h"
#include "vm.h"

class Pysk {
public: 
    Pysk() = default;
    ~Pysk() = default;
    static void run(const std::string source);
};

#endif
