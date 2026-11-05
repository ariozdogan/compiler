#include "lexer.hpp"
#include "token_type.hpp"

#include <iostream>
#include <string_view>


int main() {
    std::string_view source =  "() {} ! != , : ; + - * %";
    Lexer lexer(source);

    while (true) {
        Token t = lexer.next_token();
        std::string_view str = to_string(t.type);
        std::cout << str << std::endl;
        if (t.type == TokenType::EndOfFile) break;
    }

    return 0;
}