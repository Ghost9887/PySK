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
public:
    Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
    std::any accept(ExprVisitor &visitor) override;
};

class Grouping : public Expr, public std::enable_shared_from_this<Grouping> {
public:
    std::shared_ptr<Expr> expression;
public:
    Grouping(std::shared_ptr<Expr> expression);
    std::any accept(ExprVisitor &visitor) override;
};

class Literal : public Expr, public std::enable_shared_from_this<Literal> {
public:
    LiteralValue value;
public:
    Literal(LiteralValue value);
    std::any accept(ExprVisitor &visitor) override;
};

class Unary : public Expr, public std::enable_shared_from_this<Unary> {
public:
    Token op;
    std::shared_ptr<Expr> right;
public:
    Unary(Token op, std::shared_ptr<Expr> right);
    std::any accept(ExprVisitor &visitor) override;
};

#endif
