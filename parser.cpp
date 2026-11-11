#include "parser.hpp"
#include "token_type.hpp"

#include <algorithm>

bool Parser::is_at_end() const {
    Token token = peek();
    if (token.type == TokenType::EndOfFile) return true;

    return false;
}

Token Parser::peek() const {
    return tokens[current];
}

Token Parser::peek_next() const {
    if (current + 1 >= tokens.size()) return peek(); // guard against trying to peek token after EOF

    return tokens[current + 1];
}

Token Parser::previous() const {
    if (current == 0) return peek(); // guard against trying to peek at token before first in vector

    return tokens[current - 1];
}

Token Parser::advance() {
    return tokens[current++];
}

bool Parser::check(TokenType type) {
    Token current_token = peek();
    if (current_token.type == type) return true;

    return false;
}

bool Parser::match(TokenType type) {
    Token current_token = peek();

    if (current_token.type == type) {
        current++;
        return true;
    }
    return false;
}

bool Parser::match_any(std::initializer_list<TokenType> types) {
    Token current_token = peek();

    auto it = std::find(types.begin(), types.end(), current_token.type); 
    if (it != types.end()) {
        current++;
        return true;
    }
    
    return false;
}

std::string Parser::expect(TokenType type, std::string message) {
    Token current_token = peek();

    if (current_token.type == type) {
        current++;
        return "token matched";
    }
    return message;
}

std::string Parser::error(Token token, std::string message) {
    std::string error_message = 
        "Error: " 
        + std::to_string(token.line) 
        + ":" 
        + std::to_string(token.col) 
        + " -> "  
        + message;

    return error_message;
}