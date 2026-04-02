#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <memory>
#include "token.h"
#include "values.h"

class Expr {
public:
    virtual std::string to_string() = 0;
    virtual ~Expr() = default;
};

class BinaryExpr : public Expr {
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
public:
    BinaryExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
    std::string to_string() override;
};

class UnaryExpr: public Expr {
public:
    Token op;
    std::shared_ptr<Expr> right;
public:
    UnaryExpr(Token op, std::shared_ptr<Expr> right);
    std::string to_string() override;
};

class LiteralExpr : public Expr {
public:
    LiteralValue literal;
    int line;
public:
    LiteralExpr(LiteralValue literal, int line);
    std::string to_string() override;
};

class GroupingExpr : public Expr {
public:
    std::shared_ptr<Expr> expression;
public:
    GroupingExpr(std::shared_ptr<Expr> expression);
    std::string to_string() override;
};

class CallExpr : public Expr {
public:
    std::string name;
    int line;
public:
    CallExpr(std::string name, int line);
    std::string to_string() override;
};

#endif
