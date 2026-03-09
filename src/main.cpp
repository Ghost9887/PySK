#include "common.hpp"
#include "parser.hpp"

void run(const char *file_name) {
    Scanner scanner;
    scanner.load(file_name);
    scanner.tokenize();
    scanner.print_tokens();

    Parser parser(scanner.get_tokens());
    parser.parse();
}

void run(std::string content) {
    Scanner scanner(content);
    scanner.tokenize();
    scanner.print_tokens();
}

void repl() {
    std::string input;
    while (true) {
        std::cout << "> ";
        std::cin >> input;
        if (input == "q" || input == "quit") break;
        run(input);
    }
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
