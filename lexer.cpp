#include "lexer.hpp"
#include "token.hpp"
#include "token_type.hpp"

Lexer::Lexer(std::string_view source) : source_(source) {}

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

        // longest match tokens
        case '-': return make_token(match('>') ? TokenType::Arrow : TokenType::Minus);
        case '=': return make_token(match('=') ? TokenType::EqualEqual : TokenType::Assign);
        case '!': return make_token(match('=') ? TokenType::BangEqual : TokenType::Bang);
        case '<': return make_token(match('=') ? TokenType::LessEqual : TokenType::LessThan);
        case '>': return make_token(match('=') ? TokenType::GreaterEqual : TokenType::GreaterThan);
        case '&': return make_token(match('&') ? TokenType::And : TokenType::Invalid);
        case '|': return make_token(match('|') ? TokenType::Or : TokenType::Invalid);
    }

    return make_token(TokenType::Invalid);
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
                    while(peek() != '\n' || !is_at_end()) {
                        advance();
                    };
                    break;
                }
                else return;
            default: 
                return;
        }
    }
}

Token Lexer::make_token(TokenType type) {
    Token token;
    token.type = type;
    token.lexeme = source_.substr(start, current-start); 
    token.line = start_line;
    token.col = start_col;

    return token;
}