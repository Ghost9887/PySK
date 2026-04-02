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
            case OP_NEGATE: stack.push_back(negate(pop())); break;
            case OP_COMPARE_EQUAL: stack.push_back(compare_op("==")); break;
            case OP_COMPARE_UNEQUAL: stack.push_back(compare_op("!=")); break;
            case OP_GREATER: stack.push_back(compare_op(">")); break;
            case OP_GREATER_EQUAL: stack.push_back(compare_op(">=")); break;
            case OP_LESS: stack.push_back(compare_op("<")); break;
            case OP_LESS_EQUAL: stack.push_back(compare_op("<=")); break;
            case OP_CONSTANT: stack.push_back(read_constant()); break;
            case OP_PRINT: std::cout << Debugger::literal_to_string(pop()) << '\n'; break;
            case OP_RETURN: std::cout << "Return" << '\n'; break;
            case OP_END: return INTERPRET_OK;
            default:
                std::cout << "COMPILER ERROR" << '\n';
                return INTERPRET_COMPILE_ERROR;
        }
    }
    return INTERPRET_COMPILE_ERROR;
}

LiteralValue VM::binary_op(char op) {
    LiteralValue b = pop();
    LiteralValue a = pop();
    if (std::holds_alternative<double>(b) && std::holds_alternative<double>(a)) {
        switch (op) {
            case '+': return std::get<double>(a) + std::get<double>(b); 
            case '-': return std::get<double>(a) - std::get<double>(b);
            case '/': return std::get<double>(a) / std::get<double>(b);
            case '*': return std::get<double>(a) * std::get<double>(b);
        }
    }
    return -1.0;
}

LiteralValue VM::compare_op(std::string op) {
    LiteralValue b = pop();
    LiteralValue a = pop();
    
    if (std::holds_alternative<double>(b) && std::holds_alternative<double>(a)) {
        if (op == "==") return std::get<double>(a) == std::get<double>(b);
        else if (op == "!=") return std::get<double>(a) != std::get<double>(b);
        else if (op == ">") return std::get<double>(a) > std::get<double>(b);
        else if (op == ">=") return std::get<double>(a) >= std::get<double>(b);
        else if (op == "<") return std::get<double>(a) < std::get<double>(b);
        else return std::get<double>(a) <= std::get<double>(b);
    }else if (std::holds_alternative<bool>(b) && std::holds_alternative<bool>(b)) {
        if (op == "==") return std::get<bool>(a) == std::get<bool>(b);
        else if (op == "!=") return a != b;
    }

    return std::monostate();
}

LiteralValue VM::negate(LiteralValue value) {
    if (std::holds_alternative<double>(value)) return -std::get<double>(value);
    else if (std::holds_alternative<bool>(value)) return !std::get<bool>(value);
    else return std::monostate();
}

Byte VM::read_byte() {
    return chunk->codes.at(ip++);
}

LiteralValue VM::read_constant() {
    int index = chunk->codes.at(ip++);
    return chunk->constants->values.at(index).literal;
}

LiteralValue VM::pop() {
    LiteralValue value = stack.back();
    stack.pop_back();
    return value;
}

InterpretResult VM::interpret(std::shared_ptr<Chunk> chunk) {
    this->chunk = chunk;
    return run();
}
