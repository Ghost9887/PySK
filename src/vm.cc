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

//TODO: RUNTIME ERRORS
LiteralValue VM::binary_op(char op) {
    LiteralValue b = pop();
    LiteralValue a = pop();
    switch (op) {
        case '+': 
            if (is_number(a) && is_number(b)) return std::get<double>(a) + std::get<double>(b); 
            else if (is_string(a) && is_string(b)) return std::get<std::string>(a) + std::get<std::string>(b);
        case '-': 
            if (is_number(a) && is_number(b)) return std::get<double>(a) - std::get<double>(b);
        case '/': 
            if (is_number(a) && is_number(b)) return std::get<double>(a) / std::get<double>(b);
        case '*':{
            if (is_number(a) && is_number(b)) return std::get<double>(a) * std::get<double>(b);
            else if (is_string(a) && is_number(b)) { 
                std::string str;
                for (int i = 0; i < std::get<double>(b); i++) {
                    str += std::get<std::string>(a);
                }
                return str;
            }
        }
        default: break;
    }

    return -1.0;
}

//TODO: RUNTIME ERRROS
LiteralValue VM::compare_op(std::string op) {
    LiteralValue b = pop();
    LiteralValue a = pop();
    
    if (op == "==") {
        if (is_number(a) && is_number(b)) return std::get<double>(a) == std::get<double>(b);
        else if (is_bool(a) && is_bool(b)) return std::get<bool>(a) == std::get<bool>(b);
        else if (is_string(a) && is_string(b)) return std::get<std::string>(a) == std::get<std::string>(b);
    }
    else if (op == "!=") {
        if (is_number(a) && is_number(b)) return std::get<double>(a) != std::get<double>(b);
        else if (is_bool(a) && is_bool(b)) return std::get<bool>(a) != std::get<bool>(b);
        else if (is_string(a) && is_string(b)) return std::get<std::string>(a) != std::get<std::string>(b);
    }
    else if (op == ">") if (is_number(a) && is_number(b)) return std::get<double>(a) > std::get<double>(b);
    else if (op == ">=") if (is_number(a) && is_number(b)) return std::get<double>(a) >= std::get<double>(b);
    else if (op == "<") if (is_number(a) && is_number(b)) return std::get<double>(a) < std::get<double>(b);
    else if (is_number(a) && is_number(b)) return std::get<double>(a) <= std::get<double>(b);
    
    return std::monostate();
}

LiteralValue VM::negate(LiteralValue value) {
    if (is_number(value)) return -std::get<double>(value);
    else if (is_bool(value)) return !std::get<bool>(value);
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

bool VM::is_number(LiteralValue value) {
    return std::holds_alternative<double>(value);
} 

bool VM::is_bool(LiteralValue value) {
    return std::holds_alternative<bool>(value);
}

bool VM::is_string(LiteralValue value) {
    return std::holds_alternative<std::string>(value);
}

bool VM::is_null(LiteralValue value) {
    return std::holds_alternative<std::monostate>(value);
}

InterpretResult VM::interpret(std::shared_ptr<Chunk> chunk) {
    this->chunk = chunk;
    return run();
}
