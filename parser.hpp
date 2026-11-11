#pragma once

#include "token.hpp"
#include "ast.hpp"

#include <vector>
#include <string>
#include <memory>
#include <initializer_list>

class Parser {
    public:
        explicit Parser(std::vector<Token> tokens) : tokens(tokens) {}
        std::unique_ptr<Expr> parse_expression();

    private:
        bool is_at_end() const;
        Token peek() const;
        Token peek_next() const;
        Token previous() const; // returns token just consumed
        Token advance();
        bool check(TokenType type); // checks if current token matches given type
        bool match(TokenType type); // if token matches type, consume it and return true
        bool match_any(std::initializer_list<TokenType> types); // if token matches any type in vector, consume and return true
        std::string expect(TokenType type, std::string message); // consume token if it matches type, otherwise return error message
        std::string error(Token token, std::string message);

        size_t current = 0;
        std::vector<Token> tokens;
};