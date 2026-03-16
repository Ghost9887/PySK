#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <cstdint>
#include <memory>
#include "values.h"

using Byte = std::uint8_t; 

typedef enum {
    OP_ADD,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_CONSTANT,
    OP_RETURN,
}OpCode;

class Chunk {
public:
    Chunk();
    ~Chunk() = default;
    void write_chunk(Byte byte, int line);
    void write_constant(Value value, int line);
public:
    std::vector<Byte> codes;
    std::vector<int> lines;
    std::unique_ptr<Values> constants;
};

#endif
