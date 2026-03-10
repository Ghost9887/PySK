#ifndef EXPR_HPP
#define EXPR_HPP

#include "common.h"
#include "token.h"

class Binary;
class Grouping;
class Literal;
class Unary;

//interface
class ExprVisitor {
public:
    virtual std::any visitBinaryExpr(std::shared_ptr<Binary> expr) = 0;
    virtual std::any visitGroupingExpr(std::shared_ptr<Grouping> expr) = 0;
    virtual std::any visitLiteralExpr(std::shared_ptr<Literal> expr) = 0;
    virtual std::any visitUnaryExpr(std::shared_ptr<Unary> expr) = 0;
    virtual ~ExprVisitor() = default;
};

//abstract base class
class Expr {
public:
    virtual std::any accept(ExprVisitor &visitor) = 0;
};

class Binary : public Expr, public std::enable_shared_from_this<Binary> {
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : left(left), op(op), right(right) {}

    std::any accept(ExprVisitor &visitor) override {
        return visitor.visitBinaryExpr(shared_from_this());
    }
};

class Grouping : public Expr, public std::enable_shared_from_this<Grouping> {
public:
    std::shared_ptr<Expr> expression;

    Grouping(std::shared_ptr<Expr> expression) : expression(expression) {}

    std::any accept(ExprVisitor &visitor) override {
        return visitor.visitGroupingExpr(shared_from_this());
    }
};

class Literal : public Expr, public std::enable_shared_from_this<Literal> {
public:
    LiteralValue value;
    
    Literal(LiteralValue value) : value(value) {}

    std::any accept(ExprVisitor &visitor) override {
        return visitor.visitLiteralExpr(shared_from_this());
    }
};

class Unary : public Expr, public std::enable_shared_from_this<Unary> {
public:
    Token op;
    std::shared_ptr<Expr> right;
    
    Unary(Token op, std::shared_ptr<Expr> right) : op(op), right(right) {}

    std::any accept(ExprVisitor &visitor) override {
        return visitor.visitUnaryExpr(shared_from_this());
    }
};

#endif
