#pragma once

#include "token_type.hpp"
#include <string_view>

struct Token {
    TokenType type;
    std::string_view lexeme;
    int line;
    int col;
};