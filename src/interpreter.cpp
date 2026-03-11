#include "interpreter.h"

void Interpreter::interpret(std::shared_ptr<Expr> expr) {
    try {
        std::any value = evaluate(expr);
        //std::cout << std::to_string(value) << '\n';
    }catch (RuntimeError error) {
        Dio::runtime_error(error);
    }
}

std::any Interpreter::visitLiteralExpr(std::shared_ptr<Literal> expr) {
    return expr->value;
}

std::any Interpreter::visitBinaryExpr(std::shared_ptr<Binary> expr) {
    std::any left = evaluate(expr->left);
    std::any right = evaluate(expr->right);

    switch (expr->op.type) {
        case TokenType::GREATER:
            check_number_operand(expr->op, std::make_shared<Literal>(left), std::make_shared<Literal>(right));
            return std::get<double>(left.value) > std::get<double>(right.value);
        case TokenType::LESSER:
            check_number_operand(expr->op, std::make_shared<Literal>(left), std::make_shared<Literal>(right));
            return std::get<double>(left.value) < std::get<double>(right.value);
        case TokenType::GREATER_EQUAL:
            check_number_operand(expr->op, std::make_shared<Literal>(left), std::make_shared<Literal>(right));
            return std::get<double>(left.value) >= std::get<double>(right.value);
        case TokenType::LESSER_EQUAL:
            check_number_operand(expr->op, std::make_shared<Literal>(left), std::make_shared<Literal>(right));
            return std::get<double>(left.value) <= std::get<double>(right.value);
        case TokenType::BANG_EQUAL:
            return !is_equal(std::make_shared<Literal>(left), std::make_shared<Literal>(right));
        case TokenType::EQUAL:
            return is_equal(std::make_shared<Literal>(left), std::make_shared<Literal>(right));
        case TokenType::MINUS:
            check_number_operand(expr->op, std::make_shared<Literal>(left), std::make_shared<Literal>(right));
            return std::get<double>(left.value) - std::get<double>(right.value);
        case TokenType::PLUS:
            if (std::holds_alternative<double>(left.value) && std::holds_alternative<double>(right.value)) {
                return std::get<double>(left.value) + std::get<double>(right.value);
            }else if (std::holds_alternative<std::string>(left.value) && std::holds_alternative<std::string>(right.value)) {
                return std::get<std::string>(left.value) + std::get<std::string>(right.value);
            }else {
                throw RuntimeError(expr->op, "Operands must be numbers or strings");
            }
        case TokenType::SLASH:
            check_number_operand(expr->op, std::make_shared<Literal>(left), std::make_shared<Literal>(right));
            return std::get<double>(left.value) / std::get<double>(right.value);
        case TokenType::STAR:
            check_number_operand(expr->op, std::make_shared<Literal>(left), std::make_shared<Literal>(right));
            return std::get<double>(left.value) * std::get<double>(right.value);
    }

    return NULL;
}

std::any Interpreter::visitUnaryExpr(std::shared_ptr<Unary> expr) {
    std::any right = evaluate(expr->right);

    switch (expr->op.type) {
        case TokenType::BANG:
            return !is_truthy(std::make_shared<Literal>(right));
        case TokenType::MINUS:
            check_number_operand(expr->op, std::make_shared<Literal>(right));
            return -std::get<double>(right->value);
    }

    return std::monostate();
}

std::any Interpreter::visitGroupingExpr(std::shared_ptr<Grouping> expr) {
    return evaluate(expr->expression);
}

std::any Interpreter::evaluate(std::shared_ptr<Expr> expr) {
    return expr->accept(*this);
}

bool Interpreter::is_truthy(std::shared_ptr<Literal> literal) {
    if (std::holds_alternative<std::monostate()>(literal->value)) 
        return false;

    if (std::get<bool>(literal->value) == true && std::get<bool>(literal->value) == false) 
        return std::get<bool>(literal->value);

    return true;
}

bool Interpreter::is_equal(std::shared_ptr<Literal> right, std::shared_ptr<Literal> left) {
    if (std::holds_alternative<std::monostate()>(right->value) 
        && std::holds_alternative<std::monostate()>(left->value)) 
        return true;

    if (std::holds_alternative<std::monostate()>(right->value)) 
        return false;

    return std::get<bool>(right->value) == std::get<bool>(left->value);
}

void Interpreter::check_number_operand(Token &op, std::shared_ptr<Literal> right) {
    if (std::holds_alternative<double>(right->value)) return;
    throw RuntimeError(op, "Operand must be a number");
}

void Interpreter::check_number_operand(Token &op, std::shared_ptr<Literal> left, std::shared_ptr<Literal> right) {
    if (std::holds_alternative<double>(right->value) && std::holds_alternative<double>(left->value))
        return;
    
    throw RuntimeError(op, "Operands must be numbers");
}
