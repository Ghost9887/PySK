#ifndef CHUNK_H
#define CHUNK_H

#include "common.h"

typedef enum {
    OP_RETURN,
}OpCode;

class Chunk {
public:
    Chunk() = default;
    ~Chunk() = default;
    void write_chunk(Byte byte);
public:
    std::vector<Byte> code;
};

#endif
