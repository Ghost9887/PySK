#include "common.h"
#include "chunk.h"
#include "debugger.h"

int main(int argc, char *argv[]) {
    Chunk chunk;
    Debugger debugger;

    chunk.write_chunk(OP_RETURN);
    debugger.disassemble_chunk(chunk, "test chunk");

    return 0;
}
