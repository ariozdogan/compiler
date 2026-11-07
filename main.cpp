#include "lexer.hpp"
#include "token_type.hpp"

#include <iostream>
#include <string_view>


int main() {
    std::string_view source =  "() {} ! != , : ; + - * % \n + let const true letter";
    Lexer lexer(source);

    while (true) {
        Token t = lexer.next_token();
        std::string_view type = to_string(t.type);
        std::string_view lexeme = t.lexeme;
        int line = t.line;
        int col = t.col;
        std::cout << type << " " << t.lexeme << " " << t.line << ":" << t.col << std::endl;
        if (t.type == TokenType::EndOfFile) break;
    }

    return 0;
}