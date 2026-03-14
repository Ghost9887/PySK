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

int Chunk::add_constant(Value value) {
    constants->write_value(value);
    return constants->values.size() - 1;
}
