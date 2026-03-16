#include "dio.h"

void Dio::run(const std::string source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.tokenize();
    std::cout << tokens.size() << '\n';
    for (Token token : tokens) {
        std::cout << token.to_string() << '\n';
    }
}
