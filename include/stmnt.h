#ifndef STMNT_H
#define STMNT_H

#include <memory>
#include "expr.h"

class Stmnt {
public:
    virtual std::string to_string() = 0;
    virtual ~Stmnt() = default;
};

class ExpressionStmnt : public Stmnt {
public:
    std::shared_ptr<Expr> expr;
public:
    ExpressionStmnt(std::shared_ptr<Expr> expr);
    std::string to_string() override;
};

class PrintStmnt : public Stmnt {
public:
    std::shared_ptr<Expr> expr;
public:
    PrintStmnt(std::shared_ptr<Expr> expr);
    std::string to_string() override;
};

class DeclStmnt : public Stmnt {
public:
    std::string name;
    std::shared_ptr<Expr> expr;
public:
    DeclStmnt(std::string name, std::shared_ptr<Expr> expr);
    std::string to_string() override;
};

#endif
