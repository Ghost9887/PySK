#ifndef DIO_H
#define DIO_H

#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "scanner.h"
#include "interpreter.h"
#include "parser.h"

class Dio {
public:
    static void run_file(const char *file_name);
    static void run_prompt();
    static void error(int line, int column, const std::string message);
    static void error(Token &token, const std::string message);
    static void runtime_error(RuntimeError &error);
private:
    static void run(const std::string content);
    static void report(int line, int column, const std::string where, const std::string message);
    inline static bool had_error = false;
    inline static bool had_runtime_error = false;
    inline static Interpreter interpreter;
};

#endif
