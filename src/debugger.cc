#include "debugger.h"

void Debugger::disassemble_chunk(const Chunk &chunk, std::string name) {
    std::cout << "==" << name << "==" << '\n';

    for (int offset = 0; offset < chunk.code.size();) {
        offset = disassemble_instruction(chunk, offset);
    }
}

int Debugger::simple_instruction(std::string name, int offset) {
    std::cout << name <<'\n';
    return ++offset;
}

int Debugger::disassemble_instruction(const Chunk &chunk, int offset) {
    std::cout << std::setw(4) << std::setfill('0') << offset << " ";

    Byte instruction = chunk.code.at(offset);
    switch (instruction) {
        case OP_RETURN:
            return Debugger::simple_instruction("OP_RETURN", offset);
        default: 
            std::cout << "Uknown opcode " << instruction;
            return ++offset;
    }
}
