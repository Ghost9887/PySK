#ifndef VM_H
#define VM_H

#include <vector>
#include <string>
#include <iostream>
#include "chunk.h"
#include "debugger.h"

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
}InterpretResult;

class VM {
public:
    VM();
    ~VM() = default;
    InterpretResult interpret(std::shared_ptr<Chunk> chunk);
public:
    std::shared_ptr<Chunk> chunk;
private:
    InterpretResult run();
    Byte read_byte();
    LiteralValue read_constant();
    LiteralValue pop(); 
    LiteralValue binary_op(char op);
    LiteralValue compare_op(std::string op);
    LiteralValue negate(LiteralValue value);
    bool is_number(LiteralValue value);
    bool is_bool(LiteralValue value);
    bool is_string(LiteralValue value);
    bool is_null(LiteralValue value);
private:
    std::vector<LiteralValue> stack;
    int ip;
};

#endif
