#ifndef DIO_H
#define DIO_H

#include "common.h"
#include "token.h"
#include "scanner.h"
#include "ast_printer.h"
#include "parser.h"

class Dio {
public:
    static void run_file(const char *file_name);
    static void run_prompt();
    static void error(int line, int column, const std::string message);
    static void error(Token &token, const std::string message);
private:
    static void run(const std::string content);
    static void report(int line, int column, const std::string where, const std::string message);
    inline static bool had_error = false;
};

#endif
