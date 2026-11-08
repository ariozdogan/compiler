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
            return (bo.value ? "true" : "false"); // bo.value is 0 or 1
        }
        case ExprKind::VariableRef: {
            const VariableRefExpr& var = static_cast<const VariableRefExpr&>(expr);
            return var.value;
        }
        case ExprKind::UnaryOp: {
            const UnaryExpr& un = static_cast<const UnaryExpr&>(expr);
            return "(" + std::string(to_string(un.op)) + " " + ast_printer(*un.operand) + ")";
        }
        case ExprKind::BinaryOp: {
            const BinaryExpr& bin = static_cast<const BinaryExpr&>(expr);
            return "(" 
                + std::string(to_string(bin.op)) 
                + " " 
                + ast_printer(*bin.left) 
                + " " 
                + ast_printer(*bin.right) 
                + ")";
        }
        case ExprKind::FuncCall: {
            const FuncCall& func = static_cast<const FuncCall&>(expr);
            std::string func_statement = "(call " + func.name;
            for (const std::unique_ptr<Expr>& arg : func.args) {
                func_statement += " " + ast_printer(*arg);
            }
            func_statement += ")";
            return func_statement;
        }
    }
    return "?";
}