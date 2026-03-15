#include "vm.h"

InterpretResult VM::run() {
    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        std::cout << "      ";
        for (Value value : stack) {
            std::cout << "[ "; 
            Values::print_value(value);
            std::cout << " ]";
        }
        std::cout << '\n';
        Debugger::disassemble_instruction(*chunk, ip);
#endif
        Byte instruction;
        switch (instruction = read_byte()) {
            case OP_CONSTANT: {
                Value constant = read_constant();
                stack.push_back(constant);
                break;
            }
            case OP_NEGATE: 
                stack.push_back(-pop()); break;
            case OP_ADD: 
                binary_op('+'); break;
            case OP_SUBTRACT: 
                binary_op('-'); break;
            case OP_MULTIPLY: 
                binary_op('*'); break;
            case OP_DIVIDE: 
                binary_op('/'); break;
            case OP_RETURN: {
                Values::print_value(pop());
                return INTERPRET_OK;
            }
        }
    }
}

Value VM::pop() {
    Value value = stack.back();
    stack.pop_back();
    return value;
}

void VM::binary_op(char op) {
    double b = pop();
    double a = pop();
    switch (op) {
        case '+': stack.push_back(a + b); break; 
        case '-': stack.push_back(a - b); break;
        case '*': stack.push_back(a * b); break;
        case '/': stack.push_back(a / b); break;
    }
}

Byte VM::read_byte() {
    return chunk->code.at(ip++);
}

Value VM::read_constant() {
    return chunk->constants->values.at(read_byte());
}

InterpretResult VM::interpret(std::string source) {
    Compiler compiler;
    compiler.compile(source);
    return INTERPRET_OK;
}
