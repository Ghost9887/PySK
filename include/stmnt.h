#ifndef STMNT_H
#define STMNT_H

#include "token.h"
#include "expr.h"

class Expression;
class Print;
class Let;

//abstract base class
class Stmnt {
public:

    //interface
    class StmntVisitor {
    public:
        virtual LiteralValue visitExpressionStmnt(std::shared_ptr<Expression> stmnt) = 0;
        virtual LiteralValue visitPrintStmnt(std::shared_ptr<Print> stmnt) = 0;
        virtual LiteralValue visitLetStmnt(std::shared_ptr<Let> stmnt) = 0;
        virtual ~StmntVisitor() = default;
    };

    virtual LiteralValue accept(StmntVisitor &visitor) = 0;
};

class Expression : public Stmnt, public std::enable_shared_from_this<Expression> {
public:
    std::shared_ptr<Expr> expression;
public:
    Expression(std::shared_ptr<Expr> expression);
    LiteralValue accept(StmntVisitor &visitor) override;
};

class Print : public Stmnt, public std::enable_shared_from_this<Print> {
public:
    std::shared_ptr<Expr> expression;
public:
    Print(std::shared_ptr<Expr> expression);
    LiteralValue accept(StmntVisitor &visitor) override;
};

class Let : public Stmnt, public std::enable_shared_from_this<Let> {
public:
    Token name;
    std::shared_ptr<Expr> initializer;
public:
    Let(Token name, std::shared_ptr<Expr> initializer);
    LiteralValue accept(StmntVisitor &visitor) override;
};

#endif
