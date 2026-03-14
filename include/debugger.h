#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "common.h"
#include "chunk.h"
#include "value.h"

class Debugger {
public:
    Debugger() = default;
    ~Debugger() = default;
    void disassemble_chunk(const Chunk &chunk, std::string name);
    int disassemble_instruction(const Chunk &chunk, int offset);
private:
    static int simple_instruction(std::string name, int offset); 
    static int constant_instruction(std::string name, const Chunk &chunk, int offset);
};

#endif
