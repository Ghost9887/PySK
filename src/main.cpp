#include "common.hpp"
#include "scanner.hpp"

void run(const char *file_name) {
    Scanner scanner;
    scanner.load(file_name);
    scanner.tokenize();
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
