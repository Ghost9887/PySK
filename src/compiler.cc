#include "compiler.h"

Compiler::Compiler() :
    chunk(std::make_shared<Chunk>()) {}

std::shared_ptr<Chunk> Compiler::compile(std::vector<std::shared_ptr<Stmnt>> statements) {
    std::cout << "Chunk Size: " << statements.size() << '\n';
    for (int i = 0; i < statements.size(); i++) {
        evaluate(statements.at(i));
    }
    chunk->write_chunk(OP_END, 0);
    return chunk;
}

void Compiler::evaluate(std::shared_ptr<Stmnt> stmnt) {
    if (auto s = std::dynamic_pointer_cast<ExpressionStmnt>(stmnt)) {
        evaluate_expression(s->expr);
    }else if (auto s = std::dynamic_pointer_cast<PrintStmnt>(stmnt)) {
        evaluate_print_stmnt(s);
    }else if (auto s = std::dynamic_pointer_cast<DeclStmnt>(stmnt)) {
        evaluate_decl_stmnt(s);
    }
    else {
        std::cout << "false" << '\n';
    }
}

void Compiler::evaluate_print_stmnt(std::shared_ptr<PrintStmnt> stmnt) {
    evaluate_expression(stmnt->expr);
    emit_byte(OP_PRINT, 0);
}

void Compiler::evaluate_decl_stmnt(std::shared_ptr<DeclStmnt> stmnt) {
    evaluate_expression(stmnt->expr);
    emit_value(stmnt->name, 0);
    emit_byte(OP_DEFINE_GLOBAL, 0);
}

void Compiler::evaluate_expression(std::shared_ptr<Expr> expr) {
    if (auto e = std::dynamic_pointer_cast<BinaryExpr>(expr)) {
        evaluate_binary_expression(e);
    }else if (auto e = std::dynamic_pointer_cast<UnaryExpr>(expr)) {
        evaluate_unary_expression(e);
    }else if (auto e = std::dynamic_pointer_cast<LiteralExpr>(expr)) {
        evaluate_literal_expression(e);
    }else if (auto e = std::dynamic_pointer_cast<GroupingExpr>(expr)) {
        evaluate_grouping_expression(e);
    }else if (auto e = std::dynamic_pointer_cast<CallExpr>(expr)) {
        evaluate_call_expression(e);
    }
}

void Compiler::evaluate_call_expression(std::shared_ptr<CallExpr> expr) {
    emit_value(expr->name, 0);
    emit_byte(OP_GET_GLOBAL, 0);
}

void Compiler::evaluate_binary_expression(std::shared_ptr<BinaryExpr> expr) {
    evaluate_expression(expr->left);
    evaluate_expression(expr->right);

    switch (expr->op.type) {
        case T_PLUS: emit_byte(OP_ADD, get_line(expr->op)); break;
        case T_MINUS: emit_byte(OP_MINUS, get_line(expr->op)); break;
        case T_STAR: emit_byte(OP_MULTIPLY, get_line(expr->op)); break; 
        case T_SLASH: emit_byte(OP_DIVIDE, get_line(expr->op)); break; 
        case T_BANG_EQUAL: emit_byte(OP_COMPARE_UNEQUAL, get_line(expr->op)); break;
        case T_EQUAL_EQUAL: emit_byte(OP_COMPARE_EQUAL, get_line(expr->op)); break;
        case T_GREATER: emit_byte(OP_GREATER, get_line(expr->op)); break;
        case T_GREATER_EQUAL: emit_byte(OP_GREATER_EQUAL, get_line(expr->op)); break;
        case T_LESS: emit_byte(OP_LESS, get_line(expr->op)); break;
        case T_LESS_EQUAL: emit_byte(OP_LESS_EQUAL, get_line(expr->op)); break; 
        default: break;
    }
}

void Compiler::evaluate_unary_expression(std::shared_ptr<UnaryExpr> expr) {
    evaluate_expression(expr->right);
    switch (expr->op.type) {
        case T_MINUS: emit_byte(OP_NEGATE, get_line(expr->op)); break;
        case T_BANG: emit_byte(OP_NEGATE, get_line(expr->op)); break;
        default: break;
    }
}

void Compiler::evaluate_literal_expression(std::shared_ptr<LiteralExpr> expr) {
    emit_value(expr->literal, 0);
}

void Compiler::evaluate_grouping_expression(std::shared_ptr<GroupingExpr> expr) {
    evaluate_expression(expr->expression);
}

int Compiler::get_line(Token &token) {
    return token.line;
}

void Compiler::emit_byte(Byte byte, int line) {
    chunk->write_chunk(byte, line);
}

void Compiler::emit_value(LiteralValue value, int line) {
    chunk->write_constant(value, line);
}
