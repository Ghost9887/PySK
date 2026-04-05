#include "debugger.h"

int Debugger::get_line(std::shared_ptr<Chunk> chunk, int offset) {
    int counter = 0;
    for (int i = 0; i < chunk->lines.size(); i+=2) {
        counter += chunk->lines.at(i);
        if (offset < counter) return chunk->lines.at(i + 1);
    }

    return -1;
}

int Debugger::print_jump_instruction(const std::string name, std::shared_ptr<Chunk> chunk, int offset) {
    std::cout << "  " << name;
    int jump_count = chunk->jumps.back();
    std::cout << "  " << jump_count << '\n';
    return ++offset;
}

int Debugger::print_simple_instruction(const std::string name, int offset) {
    std::cout << "  " << name << '\n';
    return ++offset;
}

int Debugger::print_constant_instruction(const std::string name, std::shared_ptr<Chunk> chunk, int offset) {
    std::cout << "  " << name;
    LiteralValue value = chunk->constants->values.at(chunk->codes.at(offset + 1)).literal;
    std::cout << "  " << "'" << Debugger::literal_to_string(value) << "'" << '\n';
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
        case OP_COMPARE_EQUAL: return Debugger::print_simple_instruction("OP_COMPARE_EQUAL", offset);
        case OP_COMPARE_UNEQUAL: return Debugger::print_simple_instruction("OP_COMPARE_UNEQUAL", offset);
        case OP_GREATER: return Debugger::print_simple_instruction("OP_GREATER", offset);
        case OP_GREATER_EQUAL: return Debugger::print_simple_instruction("OP_GREATER_EQUAL", offset);
        case OP_LESS: return Debugger::print_simple_instruction("OP_LESS", offset);
        case OP_LESS_EQUAL: return Debugger::print_simple_instruction("OP_LESS_EQUAL", offset);
        case OP_CONSTANT: return Debugger::print_constant_instruction("OP_CONSTANT", chunk, offset);
        case OP_PRINT: return Debugger::print_simple_instruction("OP_PRINT", offset);
        case OP_DEFINE_GLOBAL: return Debugger::print_simple_instruction("OP_DEFINE_GLOBAL", offset);
        case OP_GET_GLOBAL: return Debugger::print_simple_instruction("OP_GET_GLOBAL", offset);
        case OP_IF: return Debugger::print_simple_instruction("OP_IF", offset);
        case OP_INAK: return Debugger::print_simple_instruction("OP_INAK", offset);
        case OP_JUMP: return Debugger::print_jump_instruction("OP_JUMP", chunk, offset);
        case OP_RETURN: return Debugger::print_simple_instruction("OP_RETURN", offset);
        case OP_END: return Debugger::print_simple_instruction("OP_END", offset);
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

void Debugger::print_stack(std::vector<LiteralValue> &stack) {
    for (LiteralValue v : stack) {
        std::cout << "----" << Debugger::literal_to_string(v) << "----" << '\n';
    }
}

std::string Debugger::literal_to_string(LiteralValue literal) {
    return std::visit([](auto &&arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::string>) {
            return arg;
        } else if constexpr (std::is_arithmetic_v<T>) {
            return std::to_string(arg);
        } else if constexpr (std::is_same_v<T, bool>) {
            return arg ? "pravda" : "nepravda";
        } else {
            return "nic";
        }
    }, literal);
}
