#include "ast.hpp"

std::string ast_printer(const Expr& expr) {
    switch (expr.kind) {
        case ExprKind::IntLiteral: { // bracket makes variables inside local
            const IntLiteralExpr& lit = static_cast<const IntLiteralExpr&>(expr);
            return std::to_string(lit.value);
        }
        case ExprKind::FloatLiteral: {
            const FloatLiteralExpr& flo = static_cast<const FloatLiteralExpr&>(expr);
            return std::to_string(flo.value);
        }
        case ExprKind::StringLiteral: {
            const StringLiteralExpr& str = static_cast<const StringLiteralExpr&>(expr);
            return str.value;
        }
        case ExprKind::BoolLiteral: {
            const BoolLiteralExpr& bo = static_cast<const BoolLiteralExpr&>(expr);
            return std::to_string(bo.value);
        }
        case ExprKind::VariableRef: {
            const VariableRefExpr& var = static_cast<const VariableRefExpr&>(expr);
            return var.value;
        }
        case ExprKind::UnaryOp: {
            const UnaryExpr& unary = static_cast<const UnaryExpr&>(expr);
            return "(" + std::string(to_string(unary.unary_op)) + " " + ast_printer(*unary.operand) + ")";
        }
    }
    return "?";
}