#include "expr.h"

BinaryExpr::BinaryExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) :
    left(left), op(op), right(right) {}
std::string BinaryExpr::to_string() {
    return "BinaryExpr {" + left->to_string() + ", " + right->to_string() + " }"; 
}

LiteralExpr::LiteralExpr(LiteralValue literal) :
    literal(literal) {}
std::string LiteralExpr::to_string() {
    return "LiteralExpr {" + Token::literal_to_string(literal) + "}";
}
