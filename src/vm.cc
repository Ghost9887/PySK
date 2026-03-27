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
            case OP_COMPARE_EQUAL: stack.push_back(compare_op("==")); break;
            case OP_COMPARE_UNEQUAL: stack.push_back(compare_op("!=")); break;
            case OP_GREATER: stack.push_back(compare_op(">")); break;
            case OP_GREATER_EQUAL: stack.push_back(compare_op(">=")); break;
            case OP_LESS: stack.push_back(compare_op("<")); break;
            case OP_LESS_EQUAL: stack.push_back(compare_op("<=")); break;
            case OP_CONSTANT: stack.push_back(read_constant()); break;
            case OP_PRINT: std::cout << pop() << '\n'; break;
            case OP_RETURN: std::cout << "Return" << '\n'; break;
            case OP_END: return INTERPRET_OK;
            default:
                std::cout << "COMPILER ERROR" << '\n';
                return INTERPRET_COMPILE_ERROR;
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

Value VM::compare_op(std::string op) {
    Value b = pop();
    Value a = pop();

    if (op == "==") return a == b ? 1.0 : 0.0;
    else if (op == "!=") return a != b ? 1.0 : 0.0;
    else if (op == ">") return a > b ? 1.0 : 0.0;
    else if (op == ">=") return a >= b ? 1.0 : 0.0;
    else if (op == "<") return a < b ? 1.0 : 0.0;
    else return a <= b ? 1.0 : 0.0;
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
