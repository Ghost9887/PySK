#include "vm.h"

VM::VM() : 
    chunk(nullptr), ip(0), stack() {}

InterpretResult VM::run() {
    while (true) {
        Byte instruction = read_byte();
        switch (instruction) {
            case OP_ADD: stack.push_back(binary_op('+')); break; 
            case OP_MINUS: stack.push_back(binary_op('-')); break;
            case OP_DIVIDE: stack.push_back(binary_op('/')); break;
            case OP_MULTIPLY: stack.push_back(binary_op('*')); break;
            case OP_NEGATE: stack.push_back(-pop()); break;
            case OP_RETURN: {
                std::cout << pop() << '\n';
                return INTERPRET_OK;
            }
            case OP_CONSTANT: {
                Value value = read_constant();
                stack.push_back(value);
                break;
            }
            default: return INTERPRET_COMPILE_ERROR;
        }
    }

    return INTERPRET_COMPILE_ERROR;
}

Value VM::binary_op(char op) {
    Value b = pop();
    Value a = pop();
    switch (op) {
        case '+': return a + b; 
        case '-': return a - b;
        case '/': return a / b;
        case '*': return a * b;
    }

    return -1;
}

Byte VM::read_byte() {
    return chunk->codes.at(ip++);
}

Value VM::read_constant() {
    int index = chunk->codes.at(ip++);
    return chunk->constants->values.at(index);
}

Value VM::pop() {
    Value value = stack.back();
    stack.pop_back();
    return value;
}

InterpretResult VM::interpret(std::shared_ptr<Chunk> chunk) {
    this->chunk = chunk;
    return run();
}
