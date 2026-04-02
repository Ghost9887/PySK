#ifndef STMNT_H
#define STMNT_H

#include <memory>
#include <optional>
#include "expr.h"

class Stmnt {
public:
    virtual std::string to_string() = 0;
    virtual ~Stmnt() = default;
};

class ExpressionStmnt : public Stmnt {
public:
    std::shared_ptr<Expr> expr;
    int line;
public:
    ExpressionStmnt(std::shared_ptr<Expr> expr, int line);
    std::string to_string() override;
};

class PrintStmnt : public Stmnt {
public:
    std::shared_ptr<Expr> expr;
    int line;
public:
    PrintStmnt(std::shared_ptr<Expr> expr, int line);
    std::string to_string() override;
};

class DeclStmnt : public Stmnt {
public:
    std::string name;
    std::shared_ptr<Expr> expr;
    int line;
public:
    DeclStmnt(std::string name, std::shared_ptr<Expr> expr, int line);
    std::string to_string() override;
};

class IfStmnt : public Stmnt {
public:
    std::shared_ptr<Expr> expr;
    std::shared_ptr<Stmnt> body;
    std::optional<std::shared_ptr<Stmnt>> else_body;
    int line;
public:
    IfStmnt(std::shared_ptr<Expr> expr, std::shared_ptr<Stmnt> body, 
            std::optional<std::shared_ptr<Stmnt>> else_body, int line);
    std::string to_string() override;
};

#endif
