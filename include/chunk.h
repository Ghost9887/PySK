#ifndef CHUNK_H
#define CHUNK_H

#include "common.h"
#include "value.h"

typedef enum {
    OP_RETURN,
    OP_CONSTANT,
}OpCode;

class Chunk {
public:
    Chunk();
    ~Chunk() = default;
    void write_chunk(Byte byte, int line);
    int add_constant(Value value);
public:
    std::vector<Byte> code;
    std::unique_ptr<Values> constants;
    std::vector<int> lines;
};

#endif
