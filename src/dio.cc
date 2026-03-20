#include "dio.h"

void Dio::run(const std::string source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.tokenize();

    Debugger::print_tokens(tokens);   

    Parser parser(std::move(tokens));
    std::vector<std::shared_ptr<Stmnt>> statements = parser.parse();
    Debugger::print_ast(statements);
}
