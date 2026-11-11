#include "lexer.hpp"
#include "token.hpp"
#include "token_type.hpp"

#include <cctype>
#include <string_view>
#include <unordered_map>

Lexer::Lexer(std::string_view source) : source_(source) {}

Token Lexer::make_token(TokenType type) {
    Token token;
    token.type = type;
    token.lexeme = source_.substr(start, current-start); 
    token.line = start_line;
    token.col = start_col;

    return token;
}

Token Lexer::next_token() {
    skip_whitespace_and_comments();
    start = current;

    start_line = line;
    start_col = col;

    if (is_at_end()) return make_token(TokenType::EndOfFile);

    char c = advance();

    switch (c) {
        case '(': return make_token(TokenType::LeftParen);
        case ')': return make_token(TokenType::RightParen);
        case '{': return make_token(TokenType::LeftBrace);
        case '}': return make_token(TokenType::RightBrace);
        case ',': return make_token(TokenType::Comma);
        case ';': return make_token(TokenType::SemiColon);
        case ':': return make_token(TokenType::Colon);
        case '+': return make_token(TokenType::Plus);
        case '*': return make_token(TokenType::Star);
        case '%': return make_token(TokenType::Modulo);
        case '/': return make_token(TokenType::Slash);
        case '"': return string();

        // longest match tokens: != <= etc.
        case '-': return make_token(match('>') ? TokenType::Arrow : TokenType::Minus);
        case '=': return make_token(match('=') ? TokenType::EqualEqual : TokenType::Assign);
        case '!': return make_token(match('=') ? TokenType::BangEqual : TokenType::Bang);
        case '<': return make_token(match('=') ? TokenType::LessEqual : TokenType::LessThan);
        case '>': return make_token(match('=') ? TokenType::GreaterEqual : TokenType::GreaterThan);
        case '&': return make_token(match('&') ? TokenType::And : TokenType::Invalid);
        case '|': return make_token(match('|') ? TokenType::Or : TokenType::Invalid);
    }

    if (is_digit(c)) return number(); // for characters 0-9
    if (is_alpha(c)) return identifier(); // for characters a-z 


    return make_token(TokenType::Invalid);
}

std::vector<Token> Lexer::tokenizer(std::string_view source) {
    std::vector<Token> tokens;
    Lexer lexer(source);

    while (true) {
        Token token = lexer.next_token();
        tokens.push_back(token);

        if (token.type == TokenType::EndOfFile) break;
    }

    return tokens;
}

bool Lexer::is_at_end() const {
    return current >= source_.size();
}

char Lexer::peek() const {
    if (is_at_end()) return '\0'; // end of input

    return source_[current]; // returns the next unconsumed character
}

char Lexer::peek_next() const {
    if (current + 1 >= source_.size()) return '\0';

    return source_[current + 1];
}

char Lexer::advance() {
    char c = source_[current];

    // if char consumed is the end of line
    if (c == '\n') {
        line++;
        col = 1;
    }
    else {
        col++;
    }

    return source_[current++];
}

bool Lexer::match(char expected) {
    if (is_at_end()) return false;
    if (source_[current] != expected) return false;

    advance();
    return true;
}

bool Lexer::is_digit(char c) const {
    if (std::isdigit(static_cast<unsigned char>(c))) {
        return true;
    }
    else return false;
}

void Lexer::skip_whitespace_and_comments() {
    while (true) {
        switch (peek()) {
            case ' ': // blank space
            case '\t': // tab
            case '\r': // beginning of current line
            case '\n': 
                advance();
                break;  // new line
            case '/':
                if (peek_next() == '/') {
                    while(peek() != '\n' && !is_at_end()) {
                        advance();
                    }
                    break;
                }
                else return;
            default: 
                return;
        }
    }
}

Token Lexer::string() {
    while (peek() != '"' && !is_at_end()) advance();

    if (is_at_end()) return make_token(TokenType::Invalid);

    advance(); // consume the "
    return make_token(TokenType::StringLiteral);
}

Token Lexer::number() {
    while (is_digit(peek())) advance();

    if (peek() == '.' && is_digit(peek_next())){
        advance(); // consume the .
        while (is_digit(peek())) advance();
        return make_token(TokenType::FloatLiteral);
    }
    return make_token(TokenType::IntLiteral);
}

std::unordered_map<std::string_view, TokenType> keyword_table = {
    {"let", TokenType::Let},
    {"const", TokenType::Const},
    {"func", TokenType::Func},
    {"if", TokenType::If},
    {"elif", TokenType::Elif},
    {"else", TokenType::Else},
    {"while", TokenType::While},
    {"return", TokenType::Return},
    {"true", TokenType::TypeBool},
    {"false", TokenType::TypeBool},
    {"i16", TokenType::TypeI16},
    {"i32", TokenType::TypeI32},
    {"i64", TokenType::TypeI64},
    {"f32", TokenType::TypeF32},
    {"f64", TokenType::TypeF64}
};

Token Lexer::identifier() {
    while (is_alphanumeric(peek())) advance();

    std::string_view lexeme = source_.substr(start, current-start);

    auto it = keyword_table.find(lexeme);
    if (it != keyword_table.end()) return make_token(it->second);

    return make_token(TokenType::Identifier);
}

bool Lexer::is_alpha(char c) {
    return (isalpha(static_cast<unsigned char>(c)) || c == '_');
}

bool Lexer::is_alphanumeric(char c) {
    return (isalnum(c) || c == '_');
}