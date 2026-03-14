#include "common.h"
#include "chunk.h"
#include "debugger.h"
#include "value.h"

int main(int argc, char *argv[]) {
    Chunk chunk;
    Debugger debugger;

    int constant = chunk.add_constant(1.2);
    chunk.write_chunk(OP_CONSTANT, 123);
    chunk.write_chunk(constant, 123);
    chunk.write_chunk(OP_RETURN, 123);

    debugger.disassemble_chunk(chunk, "test chunk");

    return 0;
}
