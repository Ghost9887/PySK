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
    void evaluate_print_stmnt(std::shared_ptr<PrintStmnt> stmnt);
    void evaluate_decl_stmnt(std::shared_ptr<DeclStmnt> stmnt);
    void evaluate_if_stmnt(std::shared_ptr<IfStmnt> stmnt);
    void evaluate_expression(std::shared_ptr<Expr> expr);
    void evaluate_literal_expression(std::shared_ptr<LiteralExpr> expr);
    void evaluate_unary_expression(std::shared_ptr<UnaryExpr> expr);
    void evaluate_binary_expression(std::shared_ptr<BinaryExpr> expr);
    void evaluate_grouping_expression(std::shared_ptr<GroupingExpr> expr);
    void evaluate_call_expression(std::shared_ptr<CallExpr> expr);
    int get_line(Token &token);
    void emit_byte(Byte byte, int line);
    void emit_value(LiteralValue value, int line);
    void emit_jump(int amount);
};

#endif
