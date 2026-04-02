#include "vm.h"
#include "pysk.h"

VM::VM() : 
    chunk(nullptr), ip(0), stack(), globals() {}

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
            case OP_DEFINE_GLOBAL: define_global(); break;
            case OP_GET_GLOBAL: stack.push_back(get_global()); break;
            case OP_IF: if_stmnt(); break;
            case OP_JUMP: jump(); break;
            case OP_RETURN: std::cout << "Return" << '\n'; break;
            case OP_END: return INTERPRET_OK;
            default:
                std::cout << "COMPILER ERROR" << '\n';
                return INTERPRET_COMPILE_ERROR;
        }
    }
    return INTERPRET_COMPILE_ERROR;
}

void VM::jump() {
    int new_ip = chunk->jumps.back();
    if (ip + new_ip < chunk->codes.size()) {
        ip += new_ip;
        chunk->jumps.pop_back();
    }else error("Chyba v skoku.");
}


void VM::if_stmnt() {
    LiteralValue expr = pop();
    if (is_bool(expr)) {
        if (std::get<bool>(expr)) {
            //skip the jump
            ip++;
        }    
    }else error("Operand musi byt bool.");
}

LiteralValue VM::get_global() {
    std::string name = std::get<std::string>(pop());
    if (globals.find(name) != globals.end()) {
        return globals.at(name);
    }

    return std::monostate();
}

void VM::define_global() {
    std::string name = std::get<std::string>(pop());
    LiteralValue value = pop();
    if (globals.find(name) != globals.end()) {
        //RUTNIME ERROR SHADOWING ALREADY DECALRED VARIABLE
    }else {
        globals.insert({name, value});
    }
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
        error("Operandy musia byt cisla, bool alebo struny.");
    }
    else if (op == "!=") {
        if (is_number(a) && is_number(b)) return std::get<double>(a) != std::get<double>(b);
        else if (is_bool(a) && is_bool(b)) return std::get<bool>(a) != std::get<bool>(b);
        else if (is_string(a) && is_string(b)) return std::get<std::string>(a) != std::get<std::string>(b);
        error("Operandy musia byt cisla, bool alebo struny.");
    }
    else if (op == ">") { 
        if (is_number(a) && is_number(b)) return std::get<double>(a) > std::get<double>(b);
        else error("Operandy musia byt cisla.");
    }
    else if (op == ">=") { 
        if (is_number(a) && is_number(b)) return std::get<double>(a) >= std::get<double>(b);
        else error("Operandy musia byt cisla.");
    }
    else if (op == "<") { 
        if (is_number(a) && is_number(b)) return std::get<double>(a) < std::get<double>(b);
        else error("Operandy musia byt cisla.");
    }else if (op == "<=") {
        if (is_number(a) && is_number(b)) return std::get<double>(a) <= std::get<double>(b);
        else error("Operandy musia byt cisla.");
    }
    
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
    if (stack.empty()) {
        std::cerr << "STACK UNDERFLOW at ip=" << ip << '\n';
        std::cerr << "Previous opcode: " << int(chunk->codes[ip - 1]) << '\n';
        std::abort();
    }
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

void VM::error(const std::string message) {
    int line = Debugger::get_line(chunk, ip);
    Pysk::error(message, line, RUNTIME_ERROR);
}

InterpretResult VM::interpret(std::shared_ptr<Chunk> chunk) {
    this->chunk = chunk;
    return run();
}
