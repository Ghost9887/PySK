#ifndef VM_H
#define VM_H

#include <vector>
#include <string>
#include <iostream>
#include "chunk.h"

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
    Value read_constant();
    Value pop(); 
    Value binary_op(char op);
private:
    std::vector<Value> stack;
    int ip;
};

#endif
