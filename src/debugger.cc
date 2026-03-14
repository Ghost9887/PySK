#include "debugger.h"

int Debugger::get_line(const Chunk &chunk, int offset) {
    int count = 0;
    int index = 0;

    while (true) {
        count += chunk.lines.at(index);
        if (count > offset) break;
        index += 2;
    }

    return chunk.lines.at(index + 1);
}

void Debugger::disassemble_chunk(const Chunk &chunk, std::string name) {
    std::cout << "==" << name << "==" << '\n';

    for (int offset = 0; offset < chunk.code.size();) {
        offset = disassemble_instruction(chunk, offset);
    }
}

int Debugger::constant_instruction(std::string name, const Chunk &chunk, int offset) {
    Byte constant = chunk.code.at(offset + 1);
    std::cout << name << constant << " '";
    chunk.constants->print_value(chunk.constants->values.at(constant));
    std::cout << "'\n";
    return offset + 2;
}

int Debugger::simple_instruction(std::string name, int offset) {
    std::cout << name <<'\n';
    return ++offset;
}

int Debugger::disassemble_instruction(const Chunk &chunk, int offset) {
    std::cout << std::setw(4) << std::setfill('0') << offset << " ";
    
    if (offset > 0 && Debugger::get_line(chunk, offset - 1) == Debugger::get_line(chunk, offset)) {
        std::cout << "  | ";
    }else {
        std::cout << Debugger::get_line(chunk, offset) << " ";
    }

    Byte instruction = chunk.code.at(offset);
    switch (instruction) {
        case OP_RETURN:
            return Debugger::simple_instruction("OP_RETURN", offset);
        case OP_CONSTANT:
            return Debugger::constant_instruction("OP_CONSTANT", chunk, offset);
        default: 
            std::cout << "Uknown opcode " << instruction;
            return ++offset;
    }
}
