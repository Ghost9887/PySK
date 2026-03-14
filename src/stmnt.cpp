#include "stmnt.h"

Block::Block(std::vector<std::shared_ptr<Stmnt>> statements) :
    statements(statements) {}
LiteralValue Block::accept(StmntVisitor &visitor) {
    return visitor.visitBlockStmnt(shared_from_this());
}

If::If(std::shared_ptr<Expr> condition, std::shared_ptr<Stmnt> then_branch, std::optional<std::shared_ptr<Stmnt>> else_branch) :
    condition(condition), then_branch(then_branch), else_branch(else_branch) {}
LiteralValue If::accept(StmntVisitor &visitor) {
    return visitor.visitIfStmnt(shared_from_this());
}

Function::Function(Token name, std::vector<Token> params, std::vector<std::shared_ptr<Stmnt>> body) :
    name(name), params(params), body(body) {}
LiteralValue Function::accept(StmntVisitor &visitor) {
    return visitor.visitFunctionStmnt(shared_from_this());
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

Return::Return(Token keyword, std::shared_ptr<Expr> value) :
    keyword(keyword), value(value) {}
LiteralValue Return::accept(StmntVisitor &visitor) {
    return visitor.visitReturnStmnt(shared_from_this());
}

While::While(std::shared_ptr<Expr> condition, std::shared_ptr<Stmnt> body) :
    condition(condition), body(body) {}
LiteralValue While::accept(StmntVisitor &visitor) {
    return visitor.visitWhileStmnt(shared_from_this());
}
