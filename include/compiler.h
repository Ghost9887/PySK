#ifndef COMPILER_H
#define COMPILER_H

#include "common.h"
#include "scanner.h"
#include "chunk.h"

class Compiler {
public:
    Compiler();
    ~Compiler() = default;
    bool compile(std::shared_ptr<Chunk> chunk, const std::string source) ;
private:
    void advance();
    void error_at_current(std::string message);
    void error(std::string message);
    void error_at(const Token &token, std::string message);
    void consume(TokenType type, std::string message);
    void emit_byte(Byte byte);
    void end_compiler();
    void emit_return();
    void emit_bytes(Byte byte1, Byte byte2);
private:
    std::unique_ptr<Scanner> scanner;
    std::shared_ptr<Chunk> chunk;
    std::optional<Token> current;
    std::optional<Token> previous;
    bool had_error;
    bool panic_mode;
};

#endif
