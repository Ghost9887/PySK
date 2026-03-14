#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <string>
#include <chrono>
#include "expr.h"
#include "stmnt.h"
#include "runtime_error.h"
#include "environment.h"
#include "dio_callable.h"
#include "dio_function.h"

class Dio;

class NativeClock : public DioCallable {
public:
    LiteralValue call(Interpreter &interpreter, std::vector<LiteralValue> arguments) override;
    int arity() override;
    std::string to_string() override;
};

class Interpreter : public Expr::ExprVisitor, public Stmnt::StmntVisitor, 
    public std::enable_shared_from_this<Interpreter> {
public:
    Interpreter();
    ~Interpreter() = default;
    LiteralValue visitBlockStmnt(std::shared_ptr<Block> stmnt) override;
    LiteralValue visitIfStmnt(std::shared_ptr<If> stmnt) override;
    LiteralValue visitFunctionStmnt(std::shared_ptr<Function> stmnt) override;
    LiteralValue visitLetStmnt(std::shared_ptr<Let> stmnt) override;
    LiteralValue visitWhileStmnt(std::shared_ptr<While> stmnt) override;
    LiteralValue visitExpressionStmnt(std::shared_ptr<Expression> stmnt) override;
    LiteralValue visitPrintStmnt(std::shared_ptr<Print> stmnt) override;

    LiteralValue visitAssignExpr(std::shared_ptr<Assign> expr) override;
    LiteralValue visitVariableExpr(std::shared_ptr<Variable> expr) override;
    LiteralValue visitLiteralExpr(std::shared_ptr<Literal> expr) override;
    LiteralValue visitLogicalExpr(std::shared_ptr<Logical> expr) override;
    LiteralValue visitBinaryExpr(std::shared_ptr<Binary> expr) override;
    LiteralValue visitCallExpr(std::shared_ptr<Call> expr) override;
    LiteralValue visitUnaryExpr(std::shared_ptr<Unary> expr) override;
    LiteralValue visitGroupingExpr(std::shared_ptr<Grouping> expr) override;
    void interpret(std::vector<std::shared_ptr<Stmnt>> statements);
    void execute_block(std::vector<std::shared_ptr<Stmnt>> statements, std::shared_ptr<Environment> environment);
public:
    std::shared_ptr<Environment> globals;
private:
    std::shared_ptr<Environment> env;
private:
    LiteralValue evaluate(std::shared_ptr<Expr> expr);
    void execute(std::shared_ptr<Stmnt> stmnt);
    bool is_truthy(const LiteralValue &literal);
    bool is_equal(const LiteralValue &right, const LiteralValue &left);
    void check_number_operand(Token &op, const LiteralValue &right);
    void check_number_operand(Token &op, const LiteralValue &left, const LiteralValue &right);
    void print_literal(const LiteralValue& value);
};

#endif
