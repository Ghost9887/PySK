#include "stmnt.h"

ExpressionStmnt::ExpressionStmnt(std::shared_ptr<Expr> expr) :
    expr(expr) {}
std::string ExpressionStmnt::to_string() {
    return "ExpressionStmnt {" + expr->to_string() + " }";
}

PrintStmnt::PrintStmnt(std::shared_ptr<Expr> expr) :
    expr(expr) {}
std::string PrintStmnt::to_string() {
    return "PrintStmnt {" + expr->to_string() + " }";
}
