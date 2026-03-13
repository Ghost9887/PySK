#ifndef EXPR_HPP
#define EXPR_HPP

#include "token.h"

class Assign;
class Binary;
class Grouping;
class Literal;
class Logical;
class Unary;
class Variable;

//abstract base class
class Expr {
public:

    //interface
    class ExprVisitor {
    public:
        virtual LiteralValue visitAssignExpr(std::shared_ptr<Assign> expr) = 0;
        virtual LiteralValue visitBinaryExpr(std::shared_ptr<Binary> expr) = 0;
        virtual LiteralValue visitGroupingExpr(std::shared_ptr<Grouping> expr) = 0;
        virtual LiteralValue visitLiteralExpr(std::shared_ptr<Literal> expr) = 0;
        virtual LiteralValue visitLogicalExpr(std::shared_ptr<Logical> expr) = 0;
        virtual LiteralValue visitUnaryExpr(std::shared_ptr<Unary> expr) = 0;
        virtual LiteralValue visitVariableExpr(std::shared_ptr<Variable> expr) = 0;
        virtual ~ExprVisitor() = default;
    };

    virtual LiteralValue accept(ExprVisitor &visitor) = 0;
};

class Binary : public Expr, public std::enable_shared_from_this<Binary> {
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
public:
    Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
    LiteralValue accept(ExprVisitor &visitor) override;
};

class Grouping : public Expr, public std::enable_shared_from_this<Grouping> {
public:
    std::shared_ptr<Expr> expression;
public:
    Grouping(std::shared_ptr<Expr> expression);
    LiteralValue accept(ExprVisitor &visitor) override;
};

class Literal : public Expr, public std::enable_shared_from_this<Literal> {
public:
    LiteralValue value;
public:
    Literal(LiteralValue value);
    LiteralValue accept(ExprVisitor &visitor) override;
};

class Logical : public Expr, public std::enable_shared_from_this<Logical> {
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
public:
    Logical(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
    LiteralValue accept(ExprVisitor &visitor) override;
};

class Unary : public Expr, public std::enable_shared_from_this<Unary> {
public:
    Token op;
    std::shared_ptr<Expr> right;
public:
    Unary(Token op, std::shared_ptr<Expr> right);
    LiteralValue accept(ExprVisitor &visitor) override;
};

class Variable : public Expr, public std::enable_shared_from_this<Variable> {
public:
    Token name;
public:
    Variable(Token name);
    LiteralValue accept(ExprVisitor &visitor) override;
};

class Assign : public Expr, public std::enable_shared_from_this<Assign> {
public:
    Token name;
    std::shared_ptr<Expr> value;
public:
    Assign(Token name, std::shared_ptr<Expr> value);
    LiteralValue accept(ExprVisitor &visitor) override;
};

#endif
