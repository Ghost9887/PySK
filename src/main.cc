#include <iostream>
#include <fstream>
#include "chunk.h"
#include "debugger.h"
#include "vm.h"

void run_file(const char *file_path) {
}

void repl() {
}

int main(int argc, char *argv[]) {
    VM vm;
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
    chunk->write_constant(30.0, 123);
    chunk->write_constant(100, 123);
    chunk->write_chunk(OP_ADD, 150);
    chunk->write_constant(30, 150);
    chunk->write_chunk(OP_MINUS, 150);
    chunk->write_constant(2, 160);
    chunk->write_chunk(OP_DIVIDE, 160);
    chunk->write_chunk(OP_NEGATE, 180);
    chunk->write_chunk(OP_RETURN, 200);

    Debugger::print_chunk(chunk);
    vm.interpret(chunk);
    /*
    if (argc == 1) {
        repl();
    }else if (argc == 2) {
        run_file(argv[1]);
    }else {
        std::cerr << "Usage: dio [path]" << '\n';
        exit(64);
    }
    */
    return 0;
}
