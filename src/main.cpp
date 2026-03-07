#include "common.hpp"

void run(const char *file_name) {
    std::cout << "run" << '\n';
}

void repl() {
    std::cout << "repl" << '\n';
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        std::cout << "Too many arguments" << '\n';
        std::cout << "Usage: dio [file_name]" << '\n';
    }else if (argc < 2){
        repl();
    }else {
        run(argv[1]);
    }
    return 0;
}
