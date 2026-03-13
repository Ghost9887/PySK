#include "stmnt.h"

Block::Block(std::vector<std::shared_ptr<Stmnt>> statements) :
    statements(statements) {}
LiteralValue Block::accept(StmntVisitor &visitor) {
    return visitor.visitBlockStmnt(shared_from_this());
}


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
