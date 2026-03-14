#ifndef STMNT_H
#define STMNT_H

#include <optional>

#include "token.h"
#include "expr.h"

class Block;
class If;
class Function;
class Expression;
class Print;
class Let;
class While;

//abstract base class
class Stmnt {
public:

    //interface
    class StmntVisitor {
    public:
        virtual LiteralValue visitBlockStmnt(std::shared_ptr<Block> stmnt) = 0;
        virtual LiteralValue visitIfStmnt(std::shared_ptr<If> stmnt) = 0;
        virtual LiteralValue visitFunctionStmnt(std::shared_ptr<Function> stmnt) = 0;
        virtual LiteralValue visitExpressionStmnt(std::shared_ptr<Expression> stmnt) = 0;
        virtual LiteralValue visitPrintStmnt(std::shared_ptr<Print> stmnt) = 0;
        virtual LiteralValue visitLetStmnt(std::shared_ptr<Let> stmnt) = 0;
        virtual LiteralValue visitWhileStmnt(std::shared_ptr<While> stmnt) = 0;
        virtual ~StmntVisitor() = default;
    };

    virtual LiteralValue accept(StmntVisitor &visitor) = 0;
};

class Block : public Stmnt, public std::enable_shared_from_this<Block> {
public:
    std::vector<std::shared_ptr<Stmnt>> statements;
public:
    Block(std::vector<std::shared_ptr<Stmnt>> statements);
    LiteralValue accept(StmntVisitor &visitor) override;
};

class If : public Stmnt, public std::enable_shared_from_this<If> {
public:
    std::shared_ptr<Expr> condition;
    std::shared_ptr<Stmnt> then_branch;
    std::optional<std::shared_ptr<Stmnt>> else_branch;
public:
    If(std::shared_ptr<Expr> condition, std::shared_ptr<Stmnt> then_branch, std::optional<std::shared_ptr<Stmnt>> else_branch);
    LiteralValue accept(StmntVisitor &visitor) override;
};

class Function : public Stmnt, public std::enable_shared_from_this<Function> {
public:
    Token name;
    std::vector<Token> params;
    std::vector<std::shared_ptr<Stmnt>> body;
public:
    Function(Token name, std::vector<Token> params, std::vector<std::shared_ptr<Stmnt>> body);
    LiteralValue accept(StmntVisitor &visitor) override;
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

class While : public Stmnt, public std::enable_shared_from_this<While> {
public:
    std::shared_ptr<Expr> condition;
    std::shared_ptr<Stmnt> body;
public:
    While(std::shared_ptr<Expr> condition, std::shared_ptr<Stmnt> body);
    LiteralValue accept(StmntVisitor &visitor) override;
};

#endif
