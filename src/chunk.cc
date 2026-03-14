#include "chunk.h"

Chunk::Chunk() : 
    code(), constants(std::make_unique<Values>()), lines() {}

void Chunk::write_chunk(Byte byte, int line) {
    code.push_back(byte);

    if (lines.empty()) {
        lines.push_back(1);
        lines.push_back(line);
    }else if (line == lines.back()) {
        lines.at(lines.size() - 2)++;
    }else {
        lines.push_back(1);
        lines.push_back(line);
    }
}

//TODO: add a way to store more bytes
void Chunk::write_constant(Value value, int line) {
    constants->write_value(value);
    int index = constants->values.size() - 1;

    if (index <= 256) {
        write_chunk(OP_CONSTANT, line);
        write_chunk(index, line);
    }else {
    }
}
