#include "token_type.hpp"


std::string_view to_string(TokenType kind) {
    switch(kind) {
        case TokenType::EndOfFile:
            return "EndOfFile";
        case TokenType::Invalid:
            return "Invalid";

        case TokenType::TypeI16:
            return "TypeI16";
        case TokenType::TypeI32:
            return "TypeI32";
        case TokenType::TypeI64:
            return "TypeI64";
        case TokenType::TypeF32:
            return "TypeF32";
        case TokenType::TypeF64:
            return "TypeF64";
        case TokenType::TypeStr:
            return "TypeStr";
        case TokenType::TypeBool:
            return "TypeBool";

        case TokenType::If:
            return "If";
        case TokenType::Elif:
            return "Elif";
        case TokenType::Else:
            return "Else";
        case TokenType::While:
            return "While";
        case TokenType::Func:
            return "Func";
        case TokenType::Let:
            return "Let";
        case TokenType::Const:
            return "Const";
        case TokenType::Return:
            return "Return";

        case TokenType::Identifier:
            return "Identifier";
        case TokenType::IntLiteral:
            return "IntLiteral";
        case TokenType::FloatLiteral:
            return "FloatLiteral";
        case TokenType::StringLiteral:
            return "StringLiteral";
        case TokenType::BoolLiteral:
            return "BoolLiteral";

        case TokenType::Plus:
            return "Plus";
        case TokenType::Minus:
            return "Minus";
        case TokenType::Star:
            return "Star";
        case TokenType::Slash:
            return "Slash";
        case TokenType::Modulo:
            return "Modulo";
        case TokenType::Assign:
            return "Assign";
        case TokenType::Or:
            return "Or";
        case TokenType::And:
            return "And";
        case TokenType::EqualEqual:
            return "EqualEqual";
        case TokenType::BangEqual:
            return "BangEqual";
        case TokenType::LessThan:
            return "LessThan";
        case TokenType::GreaterThan:
            return "GreaterThan";
        case TokenType::LessEqual:
            return "LessEqual";
        case TokenType::GreaterEqual:
            return "GreaterEqual";
        case TokenType::Bang:
            return "Bang";

        case TokenType::Arrow:
            return "Arrow";
        case TokenType::Colon:
            return "Colon";
        case TokenType::Comma:
            return "Comma";
        case TokenType::LeftBrace:
            return "LeftBrace";
        case TokenType::RightBrace:
            return "RightBrace";
        case TokenType::LeftParen:
            return "LeftParen";
        case TokenType::RightParen:
            return "RightParen";
        case TokenType::SemiColon:
            return "SemiColon";
    }
    return "Unknown";
}