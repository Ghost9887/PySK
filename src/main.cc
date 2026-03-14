#include "common.h"
#include "chunk.h"
#include "debugger.h"
#include "value.h"

int main(int argc, char *argv[]) {
    Chunk chunk;
    Debugger debugger;

    chunk.write_constant(1.2, 123);
    chunk.write_chunk(OP_RETURN, 123);

    chunk.write_constant(4.3, 155);
    chunk.write_chunk(OP_RETURN, 155);

    debugger.disassemble_chunk(chunk, "test chunk");

    return 0;
}
