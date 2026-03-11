#include "ast_printer.h"

std::string AstPrinter::print(Expr &expr) {
    return std::any_cast<std::string>(expr.accept(*this));
}

LiteralValue AstPrinter::visitBinaryExpr(std::shared_ptr<Binary> expr) {
    return parenthesize(expr->op.lexeme, expr->left, expr->right);
}

LiteralValue AstPrinter::visitGroupingExpr(std::shared_ptr<Grouping> expr) {
    return parenthesize("group", expr->expression);
}

LiteralValue AstPrinter::visitLiteralExpr(std::shared_ptr<Literal> expr) {
    if (std::holds_alternative<std::monostate>(expr->value)) {
        return "nic";
    }
    //universal reference
    return std::visit([](auto&& arg) -> std::string {
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

LiteralValue AstPrinter::visitUnaryExpr(std::shared_ptr<Unary> expr) {
    return parenthesize(expr->op.lexeme, expr->right);
}

template<class... T>
std::string AstPrinter::parenthesize(const std::string& name, T&&... exprs) {
    std::string output = "( " + name;
    for (auto e : {exprs...}) {
        output += " " + std::any_cast<std::string>(e->accept(*this));
    }
    output += " )";

    return output;
}

