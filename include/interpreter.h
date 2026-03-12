#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "expr.h"
#include "stmnt.h"
#include "runtime_error.h"
#include "environment.h"

class Dio;

class Interpreter : public Expr::ExprVisitor, public Stmnt::StmntVisitor, 
    public std::enable_shared_from_this<Interpreter> {
public:
    Interpreter() = default;
    ~Interpreter() = default;
    LiteralValue visitLetStmnt(std::shared_ptr<Let> stmnt) override;
    LiteralValue visitExpressionStmnt(std::shared_ptr<Expression> stmnt) override;
    LiteralValue visitPrintStmnt(std::shared_ptr<Print> stmnt) override;
    LiteralValue visitAssignExpr(std::shared_ptr<Assign> expr) override;
    LiteralValue visitVariableExpr(std::shared_ptr<Variable> expr) override;
    LiteralValue visitLiteralExpr(std::shared_ptr<Literal> expr) override;
    LiteralValue visitBinaryExpr(std::shared_ptr<Binary> expr) override;
    LiteralValue visitUnaryExpr(std::shared_ptr<Unary> expr) override;
    LiteralValue visitGroupingExpr(std::shared_ptr<Grouping> expr) override;
    void interpret(std::vector<std::shared_ptr<Stmnt>> statements);
private:
    Environment env;
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
