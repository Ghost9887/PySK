#include "compiler.h"

Compiler::Compiler() :
    scanner(nullptr), current(std::nullopt), previous(std::nullopt),
    had_error(false), panic_mode(false) {}

bool Compiler::compile(std::shared_ptr<Chunk> chunk, const std::string source) {
    scanner = std::make_unique<Scanner>(source);
    this->chunk = chunk;
    advance();
    //expression();
    consume(TOKEN_EOF, " Expect end of expression.");
    end_compiler();
    return !had_error;
}

void Compiler::advance() {
    previous = current;

    while (true) {
        current = scanner->scan_token();
        if (current.value().type != TOKEN_ERROR) break;

        error_at_current(current.value().lexeme);
    }
}

void Compiler::consume(TokenType type, std::string message) {
    if (current.value().type == type) {
        advance();
        return;
    }

    error_at_current(message);
}

void Compiler::end_compiler() {
    emit_return();
}

void Compiler::emit_return() {
    emit_byte(OP_RETURN);
}

void Compiler::emit_byte(Byte byte) {
    chunk->write_chunk(byte, previous.value().line);
}

void Compiler::emit_bytes(Byte byte1, Byte byte2) {
    emit_byte(byte1);
    emit_byte(byte2);
}

void Compiler::error_at_current(std::string message) {
    error_at(current.value(), message);
}

void Compiler::error(std::string message) {
    error_at(previous.value(), message);
}

void Compiler::error_at(const Token &token, std::string message) {
    if (panic_mode) return;
    panic_mode = true;
    std::cerr << "[line " << token.line << "] Error";

    if (token.type == TOKEN_EOF) {
        std::cerr << " at end";
    }else if (token.type == TOKEN_ERROR) {
        //NOTHING
    }else {
        std::cerr << " at " << token.lexeme;
    }

    std::cerr << message << '\n';
    had_error = true;
}
