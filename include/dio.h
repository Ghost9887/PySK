#ifndef DIO_H
#define DIO_H

#include <iostream>
#include "scanner.h"
#include "debugger.h"
#include "parser.h"
#include "compiler.h"
#include "vm.h"

typedef enum {
    PARSE_ERROR,
    RUNTIME_ERROR, 
}ErrorType;

class Dio {
public: 
    Dio() = default;
    ~Dio() = default;
    static void run(const std::string source);
    static void error(const std::string message, int line, ErrorType type);
private:
    static inline bool had_error = false;
};

#endif
