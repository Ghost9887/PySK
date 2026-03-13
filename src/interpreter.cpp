#include "interpreter.h"
#include "dio.h"

void Interpreter::interpret(std::vector<std::shared_ptr<Stmnt>> statements) {
    try {
        for (int i = 0; i < statements.size(); i++) {
            execute(statements.at(i));
        }
    }catch (RuntimeError error) {
        Dio::runtime_error(error);
    }
}

LiteralValue Interpreter::visitLetStmnt(std::shared_ptr<Let> stmnt) {
    LiteralValue value = std::monostate();
    if (stmnt->initializer != nullptr) {
        value = evaluate(stmnt->initializer);
    }

    env->define(stmnt->name, value);
    return std::monostate();
}

LiteralValue Interpreter::visitBlockStmnt(std::shared_ptr<Block> stmnt) {
    execute_block(stmnt->statements, std::make_shared<Environment>(env));
    return std::monostate();
}

LiteralValue Interpreter::visitIfStmnt(std::shared_ptr<If> stmnt) {
    LiteralValue value = evaluate(stmnt->condition);
    if (is_truthy(value)) { 
        execute(stmnt->then_branch);
    } else if (stmnt->else_branch.has_value()) {
        execute(stmnt->else_branch.value());
    }
    return std::monostate();
}

LiteralValue Interpreter::visitExpressionStmnt(std::shared_ptr<Expression> stmnt) {
    if (!stmnt->expression) {
        std::cout << "Error NULL Expression being passed in" << '\n';
        exit(1);
    }
    evaluate(stmnt->expression);
    return std::monostate();
}

LiteralValue Interpreter::visitPrintStmnt(std::shared_ptr<Print> stmnt) {
    LiteralValue value = evaluate(stmnt->expression);
    print_literal(value);
    return std::monostate();
}

LiteralValue Interpreter::visitAssignExpr(std::shared_ptr<Assign> expr) {
    LiteralValue value = evaluate(expr->value);

    env->assign(expr->name, value);
    return value;
}

LiteralValue Interpreter::visitVariableExpr(std::shared_ptr<Variable> expr) {
    return env->get(expr->name);
}

LiteralValue Interpreter::visitLiteralExpr(std::shared_ptr<Literal> expr) {
    return expr->value;
}

LiteralValue Interpreter::visitBinaryExpr(std::shared_ptr<Binary> expr) {
    LiteralValue left = evaluate(expr->left);
    LiteralValue right = evaluate(expr->right);

    switch (expr->op.type) {
        case TokenType::GREATER:
            check_number_operand(expr->op, left, right);
            return std::get<double>(left) > std::get<double>(right);
        case TokenType::LESSER:
            check_number_operand(expr->op, left, right);
            return std::get<double>(left) < std::get<double>(right);
        case TokenType::GREATER_EQUAL:
            check_number_operand(expr->op, left, right);
            return std::get<double>(left) >= std::get<double>(right);
        case TokenType::LESSER_EQUAL:
            check_number_operand(expr->op, left, right);
            return std::get<double>(left) <= std::get<double>(right);
        case TokenType::BANG_EQUAL:
            return !is_equal(left, right);
        case TokenType::EQUAL_EQUAL:
            return is_equal(left, right);
        case TokenType::MINUS:
            check_number_operand(expr->op, left, right);
            return std::get<double>(left) - std::get<double>(right);
        case TokenType::PLUS:
            if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
                return std::get<double>(left) + std::get<double>(right);
            }else if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right)) {
                return std::get<std::string>(left) + std::get<std::string>(right);
            }else {
                throw RuntimeError(expr->op, "vyraz musi byt zlozeni s cisel alebo textu");
            }
        case TokenType::PERCENT:
            check_number_operand(expr->op, left, right);
            return static_cast<int>(std::get<double>(left)) % static_cast<int>(std::get<double>(right));
        case TokenType::SLASH:
            check_number_operand(expr->op, left, right);
            return std::get<double>(left) / std::get<double>(right);
        case TokenType::STAR:
            if(std::holds_alternative<std::string>(left) && std::holds_alternative<double>(right)) {
                std::string temp = "";
                for (int i = 0; i < std::get<double>(right); i++) {
                    temp += std::get<std::string>(left);
                }
                return temp;
            }else {
                check_number_operand(expr->op, left, right);
                return std::get<double>(left) * std::get<double>(right);
            }
    }

    return std::monostate();
}

LiteralValue Interpreter::visitUnaryExpr(std::shared_ptr<Unary> expr) {
    LiteralValue right = evaluate(expr->right);

    switch (expr->op.type) {
        case TokenType::BANG:
            return !is_truthy(right);
        case TokenType::MINUS:
            check_number_operand(expr->op, right);
            return -std::get<double>(right);
    }

    return std::monostate();
}

LiteralValue Interpreter::visitGroupingExpr(std::shared_ptr<Grouping> expr) {
    return evaluate(expr->expression);
}

LiteralValue Interpreter::evaluate(std::shared_ptr<Expr> expr) {
    return expr->accept(*this);
}

void Interpreter::execute(std::shared_ptr<Stmnt> stmnt) {
    stmnt->accept(*this);
}

void Interpreter::execute_block(std::vector<std::shared_ptr<Stmnt>> statements, 
        std::shared_ptr<Environment> environment) {

    std::shared_ptr<Environment> previous = env; 
    
    env = environment;
    for (int i = 0; i < statements.size(); i++) {
        execute(statements.at(i));
    }
    env = previous;
}

bool Interpreter::is_truthy(LiteralValue &literal) {
    if (std::holds_alternative<std::monostate>(literal)) 
        return false;

    if (std::holds_alternative<bool>(literal)) 
        return std::get<bool>(literal);

    return true;
}

bool Interpreter::is_equal(LiteralValue &right, LiteralValue &left) {
    if (std::holds_alternative<std::monostate>(right) 
        && std::holds_alternative<std::monostate>(left)) 
        return true;

    if (std::holds_alternative<std::monostate>(right)) 
        return false;

    return std::get<double>(right) == std::get<double>(left);
}

void Interpreter::check_number_operand(Token &op, LiteralValue &right) {
    if (std::holds_alternative<double>(right)) return;
    throw RuntimeError(op, "vyraz musi byt zlozeni s cisel");
}

void Interpreter::check_number_operand(Token &op, LiteralValue &left, LiteralValue &right) {
    if (std::holds_alternative<double>(right) && std::holds_alternative<double>(left))
        return;
    
    throw RuntimeError(op, "vyraz musi byt zlozeni s cisel");
}

void Interpreter::print_literal(const LiteralValue& value) {
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::monostate>) {
            std::cout << "nic";
        } 
        else if constexpr (std::is_same_v<T, bool>) {
            std::cout << (arg ? "pravda" : "nepravda");
        } 
        else {
            std::cout << arg;
        }
    }, value);
    std::cout << '\n';
}
