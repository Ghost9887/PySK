#ifndef PARSE_ERROR_H
#define PARSE_ERROR_H

#include <stdexcept>

class ParseError : public std::runtime_error {
public:
    ParseError(std::string message);
    ~ParseError() = default;
};

#endif
