#include "ast_printer.h"

std::string AstPrinter::print(Expr &expr) {
    return std::any_cast<std::string>(expr.accept(*this));
}

std::any AstPrinter::visitBinaryExpr(std::shared_ptr<Binary> expr) {
    return parenthesize(expr->op.lexeme, expr->left, expr->right);
}

std::any AstPrinter::visitGroupingExpr(std::shared_ptr<Grouping> expr) {
    return parenthesize("group", expr->expression);
}

std::any AstPrinter::visitLiteralExpr(std::shared_ptr<Literal> expr) {
    if (std::holds_alternative<std::monostate>(expr->value)) {
        return "nic";
    }
    return std::visit([](auto &&arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::monostate>)
            return "nic";
        else if constexpr (std::is_same_v<T, bool>)
            return arg ? "pravda" : "nepravda";
        else if constexpr (std::is_same_v<T, std::string>)
            return arg;
        else
            return std::to_string(arg);
    }, expr->value);
}

std::any AstPrinter::visitUnaryExpr(std::shared_ptr<Unary> expr) {
    return parenthesize(expr->op.lexeme, expr->right);
}

template<typename... Expr>
std::string AstPrinter::parenthesize(const std::string& name, Expr&&... exprs) {
    std::string output = "( " + name;
    ((output += " ", output += std::any_cast<std::string>(exprs->accept(*this))), ...);
    output += " )";
    return output;
}

