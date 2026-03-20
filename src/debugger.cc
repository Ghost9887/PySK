#include "debugger.h"

int Debugger::get_line(std::shared_ptr<Chunk> chunk, int offset) {
    int counter = 0;
    for (int i = 0; i < chunk->lines.size(); i+=2) {
        counter += chunk->lines.at(i);
        if (offset < counter) return chunk->lines.at(i + 1);
    }

    return -1;
}

int Debugger::print_simple_instruction(const std::string name, int offset) {
    std::cout << "  " << name << '\n';
    return ++offset;
}

int Debugger::print_constant_instruction(const std::string name, std::shared_ptr<Chunk> chunk, int offset) {
    std::cout << "  " << name;
    Value value = chunk->constants->values.at(chunk->codes.at(offset + 1));
    std::cout << "  " << "'" << std::to_string(value) << "'" << '\n';
    return offset + 2;
}

int Debugger::print_instruction(std::shared_ptr<Chunk> chunk, int offset) {
    std::cout << std::setw(4) << std::setfill('0') << std::to_string(chunk->codes.at(offset));
    if (offset > 0 && Debugger::get_line(chunk, offset) == Debugger::get_line(chunk, offset - 1)) {
        std::cout << "  |";
    }else {
        std::cout << " " << std::to_string(Debugger::get_line(chunk, offset));
    }
    switch (chunk->codes.at(offset)) {
        case OP_ADD: return Debugger::print_simple_instruction("OP_ADD", offset);
        case OP_MINUS: return Debugger::print_simple_instruction("OP_MINUS", offset);
        case OP_MULTIPLY: return Debugger::print_simple_instruction("OP_MULTIPLY", offset);
        case OP_DIVIDE: return Debugger::print_simple_instruction("OP_DIVIDE", offset);
        case OP_NEGATE: return Debugger::print_simple_instruction("OP_NEGATE", offset);
        case OP_RETURN: return Debugger::print_simple_instruction("OP_RETURN", offset);
        case OP_CONSTANT: return Debugger::print_constant_instruction("OP_CONSTANT", chunk, offset);
        default: 
            std::cout << "Uknown byte" << '\n';
            return ++offset;
    }
}

void Debugger::print_chunk(std::shared_ptr<Chunk> chunk) {
    std::cout << "--OPCODE--" << '\n';
    for (int index = 0; index < chunk->codes.size();) {
        index = Debugger::print_instruction(chunk, index);
    }
}

void Debugger::print_tokens(std::vector<Token> tokens) {
    for (Token token : tokens) {
        std::cout << token.to_string() << '\n';
    }
}

void Debugger::print_ast(std::vector<std::shared_ptr<Stmnt>> statements) {
    for (int i = 0; i < statements.size(); i++) {
        std::cout << statements.at(i)->to_string();
    }

    std::cout << '\n';
}
