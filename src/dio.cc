#include "dio.h"

void Dio::run(const std::string source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.tokenize();

    Debugger::print_tokens(tokens);   

    Parser parser(std::move(tokens));
    std::vector<std::shared_ptr<Stmnt>> statements = parser.parse();
    Debugger::print_ast(statements);

    Compiler compiler;
    std::shared_ptr<Chunk> chunk = compiler.compile(std::move(statements));

    Debugger::print_chunk(chunk);

    if (!had_error) {
        VM vm;
        vm.interpret(chunk);
    }
}

void Dio::error(const std::string message, int line, ErrorType type) {
    had_error = true;
    
    if (type == PARSE_ERROR) {
        std::cout << "PARSE_ERROR ";
    }else {
        std::cout << "RUNTIME_ERROR ";
    }

    std::cout << "at [riadok: " << line << "], what: " << message << '\n'; 
}
