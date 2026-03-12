#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "common.h"
#include "expr.h"
#include "stmnt.h"
#include "runtime_error.h"

class Dio;

class Interpreter : public Expr::ExprVisitor, public Stmnt::StmntVisitor, 
    public std::enable_shared_from_this<Interpreter> {
public:
    Interpreter() = default;
    ~Interpreter() = default;
    LiteralValue visitExpressionStmnt(std::shared_ptr<Expression> expr) override;
    LiteralValue visitPrintStmnt(std::shared_ptr<Print> expr) override;
    LiteralValue visitLiteralExpr(std::shared_ptr<Literal> expr) override;
    LiteralValue visitBinaryExpr(std::shared_ptr<Binary> expr) override;
    LiteralValue visitUnaryExpr(std::shared_ptr<Unary> expr) override;
    LiteralValue visitGroupingExpr(std::shared_ptr<Grouping> expr) override;
    void interpret(std::vector<std::shared_ptr<Stmnt>> statements);
private:
    LiteralValue evaluate(std::shared_ptr<Expr> expr);
    void execute(std::shared_ptr<Stmnt> stmnt);
    bool is_truthy(LiteralValue &literal);
    bool is_equal(LiteralValue &right, LiteralValue &left);
    void check_number_operand(Token &op, LiteralValue &right);
    void check_number_operand(Token &op, LiteralValue &left, LiteralValue &right);
    void print_literal(const LiteralValue& value);
};

#endif
