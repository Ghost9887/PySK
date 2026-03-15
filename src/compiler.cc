#include "compiler.h"

void Compiler::compile(const std::string source) {
    Scanner scanner(source);
    int line = -1;
    while (true) {
        Token token = scanner.scan_token();
        if (token.line != line) {
            line = token.line;
            std::cout << "  " << line << " ";
        }else {
            std::cout << "  | ";
        }
        std::cout << token.to_string() << '\n';
        if (token.type == TOKEN_EOF) break;
    }
}
