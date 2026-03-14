#ifndef DIO_CALLABLE_H
#define DIO_CALLABLE_H

#include <vector>
#include "token.h"

class Interpreter;

class DioCallable {
public:
    virtual int arity() = 0;
    virtual LiteralValue call(Interpreter &interpreter, std::vector<LiteralValue> arguements) = 0;
    virtual std::string to_string() = 0;
    virtual ~DioCallable() = default;
};

#endif
