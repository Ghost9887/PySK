#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "common.h"
#include "expr.h"
#include "runtime_error.h"

class Dio;

class Interpreter : public Expr::ExprVisitor, public std::enable_shared_from_this<Interpreter> {
public:
    Interpreter() = default;
    ~Interpreter() = default;
    LiteralValue visitLiteralExpr(std::shared_ptr<Literal> expr) override;
    LiteralValue visitBinaryExpr(std::shared_ptr<Binary> expr) override;
    LiteralValue visitUnaryExpr(std::shared_ptr<Unary> expr) override;
    LiteralValue visitGroupingExpr(std::shared_ptr<Grouping> expr) override;
    void interpret(std::shared_ptr<Expr> expr);
private:
    LiteralValue evaluate(std::shared_ptr<Expr> expr);
    bool is_truthy(LiteralValue &literal);
    bool is_equal(LiteralValue &right, LiteralValue &left);
    void check_number_operand(Token &op, LiteralValue &right);
    void check_number_operand(Token &op, LiteralValue &left, LiteralValue &right);
    void print_literal(const LiteralValue& value);
};

#endif
