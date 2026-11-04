#pragma once

#include <string_view>

enum class TokenType {
    // special
    EndOfFile,
    Invalid, 

    // type names
    TypeI16,
    TypeI32,
    TypeI64,
    TypeF32,
    TypeF64,
    TypeStr,
    TypeBool,

    // keywords
    If,
    Else,
    While,
    Func,
    Let,
    Const,
    Return,

    // literals
    Identifier,
    IntLiteral,
    FloatLiteral,
    StringLiteral,
    BoolLiteral,

    // operators
    Plus,
    Minus,
    Star,
    Slash,
    Modulo,
    Assign,
    Or,
    And,
    EqualEqual,
    BangEqual,
    LessThan,
    GreaterThan,
    LessEqual,
    GreaterEqual,
    Bang,

    // punctuation
    Arrow,
    Colon,
    Comma,
    LeftBrace,
    RightBrace,
    LeftParen,
    RightParen,
    SemiColon
};

std::string_view to_string(TokenType kind);