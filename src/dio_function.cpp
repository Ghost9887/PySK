#include "dio_function.h"
#include "interpreter.h"

DioFunction::DioFunction(std::shared_ptr<Function> declaration, std::shared_ptr<Environment> closure) :
    declaration(declaration), closure(closure) {}

LiteralValue DioFunction::call(Interpreter &interpreter, std::vector<LiteralValue> arguments) {
    std::shared_ptr<Environment> env = std::make_shared<Environment>(closure);

    for (int i = 0; i < declaration->params.size(); i++) {
        env->define(declaration->params.at(i), arguments.at(i));
    }

    try {
        interpreter.execute_block(declaration->body, env);
    }catch(ReturnValue return_value) {
        return return_value.value;
    }

    return std::monostate();
}

int DioFunction::arity() {
    return declaration->params.size();
}

std::string DioFunction::to_string() {
    return "<fn " + declaration->name.lexeme = ">";
}
