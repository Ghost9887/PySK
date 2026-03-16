#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <cstdint>

using Byte = std::uint8_t; 

typedef enum {
    OP_RETURN,
}OpCode;

class Chunk {
public:
    Chunk() = default;
    ~Chunk() = default;
    void write_chunk(Byte byte);
public:
    std::vector<Byte> codes;
};

#endif
