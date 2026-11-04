#pragma once

#include "token.hpp"
#include "token_type.hpp"
#include <string_view>

class Lexer {
    public:
        explicit Lexer(std::string_view source);
        Token next_token();

    private:
        std::string_view source;
        bool is_at_end() const; // reached end of source code
        char peek() const; // next character
        char peek_next() const; // two characters in front of current pointer
        char advance(); // consumes current char and advances
        bool match(char expected); // determines if input fits token rule
        void skip_whitespace_and_comments();
        Token make_token(TokenType kind);

        size_t start = 0; // start of token
        size_t current = 0; // current char
        int line = 1;
        int col = 1;
};