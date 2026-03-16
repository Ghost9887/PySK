#ifndef PARSE_ERROR_H
#define PARSE_ERROR_H

#include <stdexcept>
#include <string>

class ParseError : public std::runtime_error {
public:
    ParseError(const std::string message);
    ~ParseError() = default;
};

#endif
