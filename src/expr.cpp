#include "expr.h"

Binary::Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) 
    : left(left), op(op), right(right) {}
std::any Binary::accept(ExprVisitor &visitor) {
        return visitor.visitBinaryExpr(shared_from_this());
}


Grouping::Grouping(std::shared_ptr<Expr> expression) 
    : expression(expression) {}
std::any Grouping::accept(ExprVisitor &visitor) {
    return visitor.visitGroupingExpr(shared_from_this());
}


Literal::Literal(LiteralValue value) 
    : value(value) {}
std::any Literal::accept(ExprVisitor &visitor) {
    return visitor.visitLiteralExpr(shared_from_this());
}

Unary::Unary(Token op, std::shared_ptr<Expr> right) 
    : op(op), right(right) {}
std::any Unary::accept(ExprVisitor &visitor) {
    return visitor.visitUnaryExpr(shared_from_this());
}
