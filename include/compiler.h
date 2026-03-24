#ifndef COMPILER_H
#define COMPILER_H

#include <vector>
#include "chunk.h"
#include "stmnt.h"

class Compiler {
public:
    Compiler();
    ~Compiler() = default;
    std::shared_ptr<Chunk> compile(std::vector<std::shared_ptr<Stmnt>> statements);
private:
    std::shared_ptr<Chunk> chunk;
private:
    void evaluate(std::shared_ptr<Stmnt> stmnt);
    void evaluate_expression(std::shared_ptr<Expr> expr);
    void evaluate_binary_expression(std::shared_ptr<BinaryExpr> expr);
    LiteralValue get_value(std::shared_ptr<Expr> expr);
    bool is_value(LiteralValue value);
    void emit_binary_expr(Value value1, Value value2, Byte byte, int line);
    int get_line(Token &token);
    void emit_byte(Byte byte, int line);
    void emit_value(Value value, int line);
};

#endif
