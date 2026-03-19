#include "expr.h"

ValueExpr::ValueExpr(std::string value) :
    value(value) {}
std::string ValueExpr::to_string() {
    return "ValueExpr { " + value + " }";
}

BinaryExpr::BinaryExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) :
    left(left), op(op), right(right) {}
std::string BinaryExpr::to_string() {
    return "BinaryExpr { " + left->to_string() + ", " + op.lexeme + ", " + right->to_string() + " }";
}

ConditionalExpr::ConditionalExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) :
    left(left), op(op), right(right) {}
std::string ConditionalExpr::to_string() {
    return "ConditionalExpr { " + left->to_string() + ", " + op.lexeme + ", " + right->to_string() + " }";
}

EqualityExpr::EqualityExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) :
    left(left), op(op), right(right) {}
std::string EqualityExpr::to_string() {
    return "EqualityExpr {" + left->to_string() + ", " + op.lexeme + ", " + right->to_string() + " }";
}

AdditiveExpr::AdditiveExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) :
    left(left), op(op), right(right) {}
std::string AdditiveExpr::to_string() {
    return "AdditiveExpr {" + left->to_string() + ", " + op.lexeme + ", " + right->to_string() + " }";
}

FactorExpr::FactorExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) :
    left(left), op(op), right(right) {}
std::string FactorExpr::to_string() {
    return "FactorExpr {" + left->to_string() + ", " + op.lexeme + ", " + right->to_string() + " }";
}

UnaryExpr::UnaryExpr(Token op, std::shared_ptr<Expr> value) :
    op(op), value(value) {}
std::string UnaryExpr::to_string() {
    return "UnaryExpr {" + op.lexeme + ", " + value->to_string() + " }";
}
