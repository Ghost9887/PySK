#include "expr.h"

BinaryExpr::BinaryExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) :
    left(left), op(op), right(right) {}
std::string BinaryExpr::to_string() {
    return "BinaryExpr {" + left->to_string() + ", " + tokens_map.at(op.type) + ", " + right->to_string() + " }"; 
}

UnaryExpr::UnaryExpr(Token op, std::shared_ptr<Expr> right) :
    op(op), right(right) {}
std::string UnaryExpr::to_string() {
    return "UnaryExpr {" + tokens_map.at(op.type) + ", " + right->to_string() + "}";
}

LiteralExpr::LiteralExpr(LiteralValue literal) :
    literal(literal) {}
std::string LiteralExpr::to_string() {
    return "LiteralExpr {" + Token::literal_to_string(literal) + "}";
}

GroupingExpr::GroupingExpr(std::shared_ptr<Expr> expression) :
    expression(expression) {}
std::string GroupingExpr::to_string() {
    return "GroupingExpr {" + expression->to_string() + " }";
}
