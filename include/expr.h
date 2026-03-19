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
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
};

class ConditionalExpr : public Expr {
public:
    ConditionalExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
    std::string to_string() override;
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
};

class EqualityExpr : public Expr {
public:
    EqualityExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
    std::string to_string() override;
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
};

class AdditiveExpr : public Expr {
public:
    AdditiveExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
    std::string to_string() override;
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
};

class FactorExpr : public Expr {
public:
    FactorExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
    std::string to_string() override;
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
};

class UnaryExpr : public Expr {
public:
    UnaryExpr(Token op, std::shared_ptr<Expr> value);
    std::string to_string() override;
public:
    Token op;
    std::shared_ptr<Expr> value;
};

#endif
