#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "common.hpp"

class Scanner {
public:
    Scanner();
    ~Scanner() = default;
    void load(const char *file_name);
    void tokenize();
private:
    std::vector<Token> tokens;
    std::string content;
    int ip;
    void advance();
};

#endif
