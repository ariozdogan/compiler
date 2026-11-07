#pragma once

#include "token.hpp"
#include "token_type.hpp"

#include <string_view>

class Lexer {
    public:
        explicit Lexer(std::string_view source);
        Token next_token();

    private:
        Token make_token(TokenType type);
        bool is_at_end() const; // reached end of source code
        char peek() const; // next character
        char peek_next() const; // two characters in front of current pointer
        char advance(); // consumes current char and advances
        bool match(char expected); // determines if input fits token rule
        bool is_digit(char c) const; // returns true if char is a digit
        void skip_whitespace_and_comments();
        Token string();
        Token number();
        Token identifier(); // checks keyword_table to see if token is a keyword or identifier (variables, function names, etc.)
        bool is_alpha(char c); // checks a-z and _
        bool is_alphanumeric(char c); // check a-z 1-0 and _
        
        std::string_view source_;
        size_t start = 0; // start of token
        size_t current = 0; // current char
        int line = 1;
        int col = 1;
        int start_line;
        int start_col;
};