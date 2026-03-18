#ifndef STMNT_H
#define STMNT_H

#include "expr.h"

class Stmnt {
public:
    virtual std::string to_string() = 0;
    virtual ~Stmnt() = default;
};

class ExpressionStmnt : public Stmnt {
public:
    ExpressionStmnt(std::shared_ptr<Expr> expr);
    std::string to_string() override;
public:
    std::shared_ptr<Expr> expr;
};


#endif
