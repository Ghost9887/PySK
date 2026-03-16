#include <iostream>
#include <fstream>
#include "chunk.h"
#include "debugger.h"

void run_file(const char *file_path) {
}

void repl() {
}

int main(int argc, char *argv[]) {
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
    chunk->write_chunk(OP_RETURN);

    Debugger::print_chunk(chunk);
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
