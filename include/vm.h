#ifndef VM_H
#define VM_H

#include "common.h"
#include "chunk.h"
#include "value.h"
#include "debugger.h"
#include "compiler.h"

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
}InterpretResult;

class VM {
public:
    VM() = default;
    ~VM() = default;
    InterpretResult interpret(const std::string source);
private:
    InterpretResult run();
    Byte read_byte();
    Value read_constant();
    Value pop();
    void binary_op(char op);
private:
    int ip;
    std::shared_ptr<Chunk> chunk;
    std::vector<Value> stack;
};

#endif
