#include "common.h"
#include "chunk.h"
#include "debugger.h"
#include "value.h"
#include "vm.h"

void repl() {
    VM vm;
    std::string source;
    while (true) {
        source.clear();
        std::cout << "dio> ";
        std::getline(std::cin, source);
        if (source == "q") exit(0);
        vm.interpret(source);
    }
}

void run_file(const char *file_path) {
    VM vm;
    std::ifstream file(file_path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    InterpretResult result = vm.interpret(source);

    if (result == INTERPRET_COMPILE_ERROR) exit(65);
    if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main(int argc, char *argv[]) {
    
    if (argc == 1) {
        repl();
    }else if (argc == 2) {
        run_file(argv[1]);
    }else {
        std::cerr << "Usage: dio [path]" << '\n';
        exit(64);
    }

    /*
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
    */
    return 0;
}
