#include "chunk.h"

void Chunk::write_chunk(Byte byte) {
    code.push_back(byte);
}
