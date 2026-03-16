#include "chunk.h"

Chunk::Chunk() :
    codes(), constants(std::make_unique<Values>()) {}

void Chunk::write_chunk(Byte byte, int line) {
    codes.push_back(byte);
    if (lines.empty()) {
        lines.push_back(1);
        lines.push_back(line);
    }else {
        if (lines.at(lines.size() - 1) == line) {
            lines.at(lines.size() - 2)++;
        }else {
            lines.push_back(1);
            lines.push_back(line);
        }
    }
}

void Chunk::write_constant(Value value, int line) {
    int index = constants->write_value(value);
    if (index <= 256) {
        write_chunk(OP_CONSTANT, line);
        write_chunk(index, line);
    }else {
        //TODO: add support for more values 
    }
}
