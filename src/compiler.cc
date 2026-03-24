#include "compiler.h"

Compiler::Compiler() :
    chunk(std::make_shared<Chunk>()) {}

std::shared_ptr<Chunk> Compiler::compile(std::vector<std::shared_ptr<Stmnt>> statements) {
    std::cout << "Size: " << statements.size() << '\n';
    for (int i = 0; i < statements.size(); i++) {
        evaluate(statements.at(i));
        chunk->write_chunk(OP_RETURN, 0);
    }
    chunk->write_chunk(OP_END, 0);
    return chunk;
}

void Compiler::evaluate(std::shared_ptr<Stmnt> stmnt) {
    if (auto s = std::dynamic_pointer_cast<ExpressionStmnt>(stmnt)) {
        evaluate_expression(s->expr);
    }else {
        std::cout << "false" << '\n';
    }
}

void Compiler::evaluate_expression(std::shared_ptr<Expr> expr) {
    if (auto e = std::dynamic_pointer_cast<BinaryExpr>(expr)) {
        evaluate_binary_expression(e);
    }else if (auto e = std::dynamic_pointer_cast<UnaryExpr>(expr)) {
        evaluate_unary_expression(e);
    }
}

void Compiler::evaluate_unary_expression(std::shared_ptr<UnaryExpr> expr) {
    LiteralValue value = get_value(expr->right);

    switch (expr->op.type) {
        case T_MINUS:
            if (is_value(value)) {
                emit_value(std::get<Value>(value), get_line(expr->op));
                emit_byte(OP_NEGATE, get_line(expr->op));
            }
            break;
        default: break;
    }
}

void Compiler::evaluate_binary_expression(std::shared_ptr<BinaryExpr> expr) {
    LiteralValue a = get_value(expr->left);
    LiteralValue b = get_value(expr->right);
    Byte code;

    switch (expr->op.type) {
        case T_PLUS:
            if (is_value(a) && is_value(b)) code = OP_ADD;
            break;
        case T_MINUS:
            if (is_value(a) && is_value(b)) code = OP_MINUS;
            break;
        case T_STAR: 
            if (is_value(a) && is_value(b)) code = OP_MULTIPLY;
            break;
        case T_SLASH: 
            if (is_value(a) && is_value(b)) code = OP_DIVIDE;
            break;
        case T_EQUAL_EQUAL: {
            if (is_value(a) && is_value(b)) {
                if (std::get<Value>(a) == std::get<Value>(b)) code = OP_TRUE;
                else code = OP_FALSE;
            }
            break;
        }
        case T_BANG_EQUAL: {
            if (is_value(a) && is_value(b)) {
                if (std::get<Value>(a) == std::get<Value>(b)) code = OP_FALSE;
                else code = OP_TRUE;
            }
            break;
        }
        case T_GREATER: {
            if (is_value(a) && is_value(b)) {
                if (std::get<Value>(a) > std::get<Value>(b)) code = OP_TRUE;
                else code = OP_FALSE;
            }
            break;
        }
        case T_GREATER_EQUAL: {
            if (is_value(a) && is_value(b)) {
                if (std::get<Value>(a) >= std::get<Value>(b)) code = OP_TRUE;
                else code = OP_FALSE;
            }
            break;
        }
        case T_LESS: {
            if (is_value(a) && is_value(b)) {
                if (std::get<Value>(a) < std::get<Value>(b)) code = OP_TRUE;
                else code = OP_FALSE;
            }
            break;
        }
        case T_LESS_EQUAL: {
            if (is_value(a) && is_value(b)) {
                if (std::get<Value>(a) <= std::get<Value>(b)) code = OP_TRUE;
                else code = OP_FALSE;
            }
            break;
        }
        defualt: break;
    }

    emit_binary_expr(std::get<Value>(a), std::get<Value>(b), code, get_line(expr->op));
}

LiteralValue Compiler::get_value(std::shared_ptr<Expr> expr) {
    if (auto e = std::dynamic_pointer_cast<LiteralExpr>(expr)) {
        return e->literal;
    }

    return std::monostate();
}

bool Compiler::is_value(LiteralValue value) {
    return std::holds_alternative<Value>(value);
}

bool Compiler::is_bool(LiteralValue value) {
    return std::holds_alternative<bool>(value);
}

int Compiler::get_line(Token &token) {
    return token.line;
}

void Compiler::emit_binary_expr(Value value1, Value value2, Byte byte, int line) {
    emit_value(value1, line);
    emit_value(value2, line);
    emit_byte(byte, line);
}

void Compiler::emit_byte(Byte byte, int line) {
    chunk->write_chunk(byte, line);
}

void Compiler::emit_value(Value value, int line) {
    chunk->write_constant(value, line);
}
