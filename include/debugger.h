#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <memory>
#include <iostream>
#include <iomanip>
#include "chunk.h"

class Debugger {
public:
    Debugger() = default;
    ~Debugger() = default;
    static void print_chunk(std::shared_ptr<Chunk> chunk);
    static int print_instruction(std::shared_ptr<Chunk> chunk, int offset);
    static int print_simple_instruction(const std::string name, int offset);
    static int print_constant_instruction(const std::string name, std::shared_ptr<Chunk> chunk, int offset);
private:
    static int get_line(std::shared_ptr<Chunk> chunk, int offset);
};
#endif

