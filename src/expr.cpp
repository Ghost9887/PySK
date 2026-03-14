#include "expr.h"

Binary::Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) 
    : left(left), op(op), right(right) {}
LiteralValue Binary::accept(ExprVisitor &visitor) {
        return visitor.visitBinaryExpr(shared_from_this());
}

Call::Call(std::shared_ptr<Expr> callee, Token paren, std::vector<std::shared_ptr<Expr>> arguments)
    : callee(callee), paren(paren), arguments(arguments) {}
LiteralValue Call::accept(ExprVisitor &visitor) {
    return visitor.visitCallExpr(shared_from_this());
}

Grouping::Grouping(std::shared_ptr<Expr> expression) 
    : expression(expression) {}
LiteralValue Grouping::accept(ExprVisitor &visitor) {
    return visitor.visitGroupingExpr(shared_from_this());
}

Literal::Literal(LiteralValue value) 
    : value(value) {}
LiteralValue Literal::accept(ExprVisitor &visitor) {
    return visitor.visitLiteralExpr(shared_from_this());
}

Logical::Logical(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) :
    left(left), op(op), right(right) {}
LiteralValue Logical::accept(ExprVisitor &visitor) {
    return visitor.visitLogicalExpr(shared_from_this());
}

Unary::Unary(Token op, std::shared_ptr<Expr> right) 
    : op(op), right(right) {}
LiteralValue Unary::accept(ExprVisitor &visitor) {
    return visitor.visitUnaryExpr(shared_from_this());
}

Variable::Variable(Token name) 
    : name(name) {}
LiteralValue Variable::accept(ExprVisitor &visitor) {
    return visitor.visitVariableExpr(shared_from_this());
}

Assign::Assign(Token name, std::shared_ptr<Expr> value)
    : name(name), value(value) {}
LiteralValue Assign::accept(ExprVisitor &visitor) {
    return visitor.visitAssignExpr(shared_from_this());
}
