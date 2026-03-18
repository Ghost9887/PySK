#include "expr.h"

ValueExpr::ValueExpr(std::string value) :
    value(value) {}
std::string ValueExpr::to_string() {
    return "ValueExpr { " + value + " }";
}

BinaryExpr::BinaryExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) :
    left(left), op(op), right(right) {}
std::string BinaryExpr::to_string() {
    return "Binary Expr { " + left->to_string() + ", " + op.lexeme + ", " + right->to_string() + " }";
}
