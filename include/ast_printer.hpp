#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include "common.h"
#include "expr.hpp"

class AstPrinter : public ExprVisitor, public std::enable_shared_from_this<AstPrinter> {
public:
    AstPrinter() = default;
    ~AstPrinter() = default;

    std::string print(Expr &expr) {
        return std::any_cast<std::string>(expr.accept(*this));
    }

    std::any visitBinaryExpr(std::shared_ptr<Binary> expr) override {
        return parenthesize(expr->op.lexeme, expr->left, expr->right);
    }

    std::any visitGroupingExpr(std::shared_ptr<Grouping> expr) override {
        return parenthesize("group", expr->expression);
    }

    std::any visitLiteralExpr(std::shared_ptr<Literal> expr) override {
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

    std::any visitUnaryExpr(std::shared_ptr<Unary> expr) override {
        return parenthesize(expr->op.lexeme, expr->right);
    }
private:
    template<typename... Expr>
    std::string parenthesize(const std::string& name, Expr&&... exprs) {
        std::string output = "( " + name;

        ((output += " ", output += std::any_cast<std::string>(exprs->accept(*this))), ...);

        output += " )";
        return output;
    }
};
#endif
