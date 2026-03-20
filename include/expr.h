#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <memory>
#include "token.h"

class Expr {
public:
    virtual std::string to_string() = 0;
    virtual ~Expr() = default;
};

class BinaryExpr : public Expr{
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
public:
    BinaryExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
    std::string to_string() override;
};

#endif
