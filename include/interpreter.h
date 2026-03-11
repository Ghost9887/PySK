#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "common.h"
#include "expr.h"
#include "runtime_error.h"
#include "dio.h"

class Interpreter : public Expr::ExprVisitor, public std::enable_shared_from_this<Interpreter> {
public:
    Interpreter() = default;
    ~Interpreter() = default;
    std::any visitLiteralExpr(std::shared_ptr<Literal> expr) override;
    std::any visitBinaryExpr(std::shared_ptr<Binary> expr) override;
    std::any visitUnaryExpr(std::shared_ptr<Unary> expr) override;
    std::any visitGroupingExpr(std::shared_ptr<Grouping> expr) override;
    void interpret(std::shared_ptr<Expr> expr);
private:
    std::any evaluate(std::shared_ptr<Expr> expr);
    bool is_truthy(std::shared_ptr<Literal> value);
    bool is_equal(std::shared_ptr<Literal> right, std::shared_ptr<Literal> left);
    void check_number_operand(Token &op, std::shared_ptr<Literal> right);
    void check_number_operand(Token &op, std::shared_ptr<Literal> left, std::shared_ptr<Literal> right);
};

#endif
