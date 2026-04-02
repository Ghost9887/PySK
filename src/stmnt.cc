#include "stmnt.h"

ExpressionStmnt::ExpressionStmnt(std::shared_ptr<Expr> expr, int line) :
    expr(expr), line(line) {}
std::string ExpressionStmnt::to_string() {
    return "ExpressionStmnt {" + expr->to_string() + " }";
}

PrintStmnt::PrintStmnt(std::shared_ptr<Expr> expr, int line) :
    expr(expr), line(line) {}
std::string PrintStmnt::to_string() {
    return "PrintStmnt {" + expr->to_string() + " }";
}

DeclStmnt::DeclStmnt(std::string name, std::shared_ptr<Expr> expr, int line) :
    name(name), expr(expr), line(line) {}
std::string DeclStmnt::to_string() {
    return "DeclStmnt {" + name + ", " + expr->to_string() + " }";
}

IfStmnt::IfStmnt(std::shared_ptr<Expr> expr, std::shared_ptr<Stmnt> body, std::optional<std::shared_ptr<Stmnt>> else_body, int line) :
    expr(expr), body(body), else_body(else_body), line(line) {}
std::string IfStmnt::to_string() {
    return "IfStmnt {" + expr->to_string() + body->to_string() +  " }";
}
