#include "parse_error.h"

ParseError::ParseError(std::string message) :
    std::runtime_error(message) {}
