#pragma once

#include "token_type.hpp"
#include "token.hpp"

#include <memory>
#include <string>
#include <cstdint>

enum class ExprKind {
    IntLiteral,
    FloatLiteral,
    StringLiteral,
    BoolLiteral,
    VariableRef,
    UnaryOp,
    BinaryOp,
    FuncCall
};

struct Expr {
    ExprKind kind;
    int line;
    int col;

    Expr(ExprKind kind, int line, int col) : kind(kind), line(line), col(col) {}
    virtual ~Expr() = default; // virtual destructor correctly destorys derived nodes on AST
};

struct IntLiteralExpr : Expr {
    std::int64_t value;

    IntLiteralExpr(std::int64_t value, int line, int col) 
        : Expr(ExprKind::IntLiteral, line, col), value(value) {}
};

struct FloatLiteralExpr : Expr {
    double value; // floating point value

    FloatLiteralExpr(double value, int line, int col)
        : Expr(ExprKind::FloatLiteral, line, col), value(value) {}
};

struct StringLiteralExpr : Expr {
    std::string value;

    StringLiteralExpr(std::string value, int line, int col) 
        : Expr(ExprKind::StringLiteral, line, col), value(value) {}
};

struct BoolLiteralExpr : Expr {
    bool value;

    BoolLiteralExpr(bool value, int line, int col)
        : Expr(ExprKind::BoolLiteral, line, col), value(value) {}
};

struct VariableRefExpr : Expr {
    std::string value;

    VariableRefExpr(std::string value, int line, int col)
        : Expr(ExprKind::VariableRef, line, col), value(value) {}
};

struct UnaryExpr : Expr {
    TokenType unary_op;
    std::unique_ptr<Expr> operand; // operand is its own subtree, ex. -(1 + 2)

    UnaryExpr(TokenType unary_op, std::unique_ptr<Expr> operand, int line, int col)
        : Expr(ExprKind::UnaryOp, line, col), unary_op(unary_op), operand(std::move(operand)) {}
};

// inherits from Expr and adds binary specific data
struct BinaryExpr : Expr {
    TokenType op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;

    BinaryExpr(TokenType op, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right, int line, int col)
        : Expr(ExprKind::BinaryOp, line, col), op(op), left(std::move(left)), right(std::move(right)) {}

};

std::string ast_printer(const Expr& expr);