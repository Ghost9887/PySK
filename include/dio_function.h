#ifndef DIO_FUNCTION_H
#define DIO_FUNCTION_H

#include <string>
#include <memory>
#include "dio_callable.h"
#include "stmnt.h"
#include "environment.h"

class Interpreter;

class DioFunction : public DioCallable {
public:
    DioFunction(std::shared_ptr<Function> declaration);
    ~DioFunction() = default;
    LiteralValue call(Interpreter &interpreter, std::vector<LiteralValue> arguments) override;
    int arity() override;
    std::string to_string() override;
private:
    std::shared_ptr<Function> declaration;
};

#endif
