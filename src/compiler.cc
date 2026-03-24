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
    }
}

void Compiler::evaluate_binary_expression(std::shared_ptr<BinaryExpr> expr) {
    LiteralValue a = get_value(expr->left);
    LiteralValue b = get_value(expr->right);

    switch (expr->op.type) {
        case T_PLUS: {
            //double
            if (std::holds_alternative<Value>(a) && std::holds_alternative<Value>(b)) {
                emit_value(std::get<Value>(a), get_line(expr->op));
                emit_value(std::get<Value>(b), get_line(expr->op));
                emit_byte(OP_ADD, get_line(expr->op));
            }
            break;
        }
        case T_MINUS: {
            //double
            if (std::holds_alternative<Value>(a) && std::holds_alternative<Value>(b)) {
                emit_value(std::get<Value>(a), get_line(expr->op));
                emit_value(std::get<Value>(b), get_line(expr->op));
                emit_byte(OP_MINUS, get_line(expr->op));
            }
            break;
        }
        case T_STAR: {
            //double
            if (std::holds_alternative<Value>(a) && std::holds_alternative<Value>(b)) {
                emit_value(std::get<Value>(a), get_line(expr->op));
                emit_value(std::get<Value>(b), get_line(expr->op));
                emit_byte(OP_MULTIPLY, get_line(expr->op));
            }
            break;
        }
        case T_SLASH: {
            //double
            if (std::holds_alternative<Value>(a) && std::holds_alternative<Value>(b)) {
                emit_value(std::get<Value>(a), get_line(expr->op));
                emit_value(std::get<Value>(b), get_line(expr->op));
                emit_byte(OP_DIVIDE, get_line(expr->op));
            }
            break;
        }
        defualt: break;
    }
}

LiteralValue Compiler::get_value(std::shared_ptr<Expr> expr) {
    if (auto e = std::dynamic_pointer_cast<LiteralExpr>(expr)) {
            return e->literal;
    }

    return std::monostate();
}

int Compiler::get_line(Token &token) {
    return token.line;
}

void Compiler::emit_byte(Byte byte, int line) {
    chunk->write_chunk(byte, line);
}

void Compiler::emit_value(Value value, int line) {
    chunk->write_constant(value, line);
}
