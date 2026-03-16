#include "parse_error.h"

ParseError::ParseError(const std::string message) :
    std::runtime_error(message) {}
