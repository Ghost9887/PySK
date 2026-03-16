#include "chunk.h"

void Chunk::write_chunk(Byte byte) {
    codes.push_back(byte);
}
