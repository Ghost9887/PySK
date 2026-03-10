#include "common.h"
#include "dio.h"
#include "ast_printer.hpp"

int main(int argc, char *argv[]) {
    
    std::shared_ptr<Expr> expression =
        std::make_shared<Binary>(
            std::make_shared<Unary>(
                Token(TokenType::MINUS, "-", std::monostate(), 1, 1),
                std::make_shared<Literal>(123)
            ),
            Token(TokenType::STAR, "*", std::monostate(), 1, 1),
            std::make_shared<Grouping>(
                std::make_shared<Literal>(45.67)
            )
        );

    AstPrinter printer;
    std::cout << printer.print(*expression) << '\n';



    /*
    if (argc > 2) {
        std::cout << "Usage: ./dio [file_name]" << '\n';
    }
    else if (argc == 2) {
        Dio::run_file(argv[1]);
    }else {
        Dio::run_prompt();
    }
    */
    return 0;
}
