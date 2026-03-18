#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <memory>
#include "values.h"
#include "token.h"

class Expr {
public:
    virtual std::string to_string() = 0;
    virtual ~Expr() = default;
};

class ValueExpr : public Expr {
public:
    ValueExpr(std::string value);
    std::string to_string() override;
public:
    std::string value;
};

class BinaryExpr : public Expr {
public:
    BinaryExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
    std::string to_string() override;
public:
    std::shared_ptr<Expr> right;
    Token op;
    std::shared_ptr<Expr> left;
};

#endif
