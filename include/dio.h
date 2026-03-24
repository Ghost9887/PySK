#ifndef DIO_H
#define DIO_H

#include <iostream>
#include "scanner.h"
#include "debugger.h"
#include "parser.h"
#include "compiler.h"
#include "vm.h"

class Dio {
public: 
    Dio() = default;
    ~Dio() = default;
    static void run(const std::string source);
};

#endif
