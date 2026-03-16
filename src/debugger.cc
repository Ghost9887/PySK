#include "debugger.h"

int Debugger::print_simple_instruction(const std::string name, int offset) {
    std::cout << "   " << name << '\n';
    return ++offset;
}

int Debugger::print_instruction(std::shared_ptr<Chunk> chunk, int offset) {
    std::cout << std::setw(5) << std::setfill('0') << chunk->codes.at(offset);
    switch (chunk->codes.at(offset)) {
        case OP_RETURN: return Debugger::print_simple_instruction("OP_RETURN", offset);
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
