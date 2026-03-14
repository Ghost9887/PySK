#include "dio_function.h"
#include "interpreter.h"

DioFunction::DioFunction(std::shared_ptr<Function> declaration) :
    declaration(declaration) {}

LiteralValue DioFunction::call(Interpreter &interpreter, std::vector<LiteralValue> arguments) {
    std::shared_ptr<Environment> env = std::make_shared<Environment>(interpreter.globals);

    for (int i = 0; i < declaration->params.size(); i++) {
        env->define(declaration->params.at(i), arguments.at(i));
    }
    
    interpreter.execute_block(declaration->body, env);
    return std::monostate();
}

int DioFunction::arity() {
    return declaration->params.size();
}

std::string DioFunction::to_string() {
    return "<fn " + declaration->name.lexeme = ">";
}
