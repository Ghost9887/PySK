#ifndef DIO_H
#define DIO_H

#include <iostream>
#include "scanner.h"
#include "parser.h"
#include "debugger.h"

class Dio {
public: 
    Dio() = default;
    ~Dio() = default;
    static void run(const std::string source);
};

#endif
