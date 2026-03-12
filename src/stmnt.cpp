#include "stmnt.h"

Expression::Expression(std::shared_ptr<Expr> expression) :
    expression(expression) {}
LiteralValue Expression::accept(StmntVisitor &visitor) {
    return visitor.visitExpressionStmnt(shared_from_this());   
}

Print::Print(std::shared_ptr<Expr> expression) :
    expression(expression) {}
LiteralValue Print::accept(StmntVisitor &visitor) {
    return visitor.visitPrintStmnt(shared_from_this());
}

Let::Let(Token name, std::shared_ptr<Expr> initializer) :
    name(name), initializer(initializer) {}
LiteralValue Let::accept(StmntVisitor &visitor) {
    return visitor.visitLetStmnt(shared_from_this());
}
