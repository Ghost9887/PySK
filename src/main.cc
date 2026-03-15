#include "common.h"
#include "chunk.h"
#include "debugger.h"
#include "value.h"
#include "vm.h"

int main(int argc, char *argv[]) {
    VM vm;
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();

    chunk->write_constant(1.2, 123);
    chunk->write_constant(3.4, 123);
    chunk->write_chunk(OP_ADD, 123);
    chunk->write_constant(5.6, 123);
    chunk->write_chunk(OP_DIVIDE, 123);
    chunk->write_chunk(OP_NEGATE, 123);
    chunk->write_chunk(OP_RETURN, 123);
    
    //Debugger::disassemble_chunk(*chunk, "test chunk");
    vm.interpret(chunk);
    return 0;
}
