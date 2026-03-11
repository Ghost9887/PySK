#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "common.h"
#include "expr.h"

class AstPrinter : public Expr::ExprVisitor, public std::enable_shared_from_this<AstPrinter> {
public:
    AstPrinter() = default;
    ~AstPrinter() = default;
    std::string print(Expr &expr);
    std::any visitBinaryExpr(std::shared_ptr<Binary> expr) override;
    std::any visitGroupingExpr(std::shared_ptr<Grouping> expr) override;
    std::any visitLiteralExpr(std::shared_ptr<Literal> expr) override;
    std::any visitUnaryExpr(std::shared_ptr<Unary> expr) override;
private:
    template<class... T>
    std::string parenthesize(const std::string& name, T&&... exprs);
};
#endif
