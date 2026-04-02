#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <memory>
#include <iostream>
#include <iomanip>
#include "chunk.h"
#include "token.h"
#include "stmnt.h"

class Debugger {
public:
    Debugger() = default;
    ~Debugger() = default;
    static void print_tokens(std::vector<Token> tokens);
    static void print_ast(std::vector<std::shared_ptr<Stmnt>> statements);
    static void print_stack(std::vector<LiteralValue> &stack);
    static void print_chunk(std::shared_ptr<Chunk> chunk);
    static int print_instruction(std::shared_ptr<Chunk> chunk, int offset);
    static int print_simple_instruction(const std::string name, int offset);
    static int print_constant_instruction(const std::string name, std::shared_ptr<Chunk> chunk, int offset);
    static int print_jump_instruction(const std::string name, std::shared_ptr<Chunk> chunk, int offset);
    static std::string literal_to_string(LiteralValue literal);
    static int get_line(std::shared_ptr<Chunk> chunk, int offset);
};
#endif

