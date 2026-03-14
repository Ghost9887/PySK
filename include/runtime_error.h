#ifndef RUNTIME_ERROR_H
#define RUNTIME_ERROR_H

#include <stdexcept>
#include "token.h"

class RuntimeError : public std::runtime_error {
public:
    RuntimeError(Token &token, std::string message);
    ~RuntimeError() = default;
    Token &token;
};

#endif
