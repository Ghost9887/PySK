#ifndef RETURN_VALUE_H
#define RETURN_VALUE_H

#include <stdexcept>
#include "token.h"

class ReturnValue: public std::runtime_error {
public:
    ReturnValue(LiteralValue value);
    ~ReturnValue() = default;
public:
    LiteralValue value;
};

#endif
