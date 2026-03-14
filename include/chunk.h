#ifndef CHUNK_H
#define CHUNK_H

#include "common.h"
#include "value.h"

typedef enum {
    OP_RETURN,
    OP_CONSTANT,
    OP_CONSTANT_LONG,
}OpCode;

class Chunk {
public:
    Chunk();
    ~Chunk() = default;
    void write_chunk(Byte byte, int line);
    void write_constant(Value value, int line);
public:
    std::vector<Byte> code;
    std::unique_ptr<Values> constants;
    std::vector<int> lines;
};

#endif
