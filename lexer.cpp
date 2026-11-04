#include "lexer.hpp"

Lexer::Lexer(std::string_view source) : source(source) {}

bool Lexer::is_at_end() const {
    return current >= source.size();
}