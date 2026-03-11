#include "dio.h"

void Dio::run(const std::string content) {
    Scanner scanner(content);
    std::vector<Token> tokens = scanner.scan_tokens();
    Parser parser(tokens);
    std::shared_ptr<Expr> expression = parser.parse();

    if (had_error) return;
    
    AstPrinter printer;
    std::cout << printer.print(*expression) << '\n';
}

void Dio::run_file(const char *file_name) {
    std::ifstream file(file_name);

    if (!file.is_open()) {
        std::cerr << "Chyba pri citani suboru: " << file_name << '\n';
        exit(1);
        return;
    }

    std::string content;
    std::string line;
    while(std::getline(file, line)) {
        content += line;
    }

    file.close();
    run(content);   

    if (had_error) exit(1);
}

void Dio::run_prompt() {
    while (true) {
        std::string content;
        std::cout << "dio> ";
        getline(std::cin, content);
        if (content == "q") break;
        run(content);
        had_error = false;
    }
}

void Dio::error(Token &token, const std::string message) {
    if (token.type == TokenType::_EOF) {
        report(token.line, token.column, "na konci", message);
    }else {
        report(token.line, token.column, "na '" + token.lexeme + "'", message);
    }
}

void Dio::error(int line, int column, const std::string message) {
    report(line, column,  "", message);
}

void Dio::report(int line, int column, const std::string where, const std::string message) {
    std::cerr 
        << "[riadok: " 
        << line 
        << ", stlpec: " 
        << column 
        << "] Chyba " 
        << where 
        << ": " 
        << message 
        << '\n';
    had_error = true;
}
