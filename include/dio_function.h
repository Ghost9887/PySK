#ifndef DIO_FUNCTION_H
#define DIO_FUNCTION_H

#include <string>
#include <memory>
#include "dio_callable.h"
#include "stmnt.h"
#include "environment.h"
#include "return_value.h"

class Interpreter;

class DioFunction : public DioCallable {
public:
    DioFunction(std::shared_ptr<Function> declaration, std::shared_ptr<Environment> closure);
    ~DioFunction() = default;
    LiteralValue call(Interpreter &interpreter, std::vector<LiteralValue> arguments) override;
    int arity() override;
    std::string to_string() override;
private:
    std::shared_ptr<Function> declaration;
    std::shared_ptr<Environment> closure;
};

#endif
