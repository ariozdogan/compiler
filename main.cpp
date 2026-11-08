#include "lexer.hpp"
#include "token.hpp"
#include "token_type.hpp"
#include "ast.hpp"

#include <iostream>
#include <memory>
#include <string_view>

void test_lexer() {
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
}



int main() {
    std::unique_ptr<Expr> one = std::make_unique<IntLiteralExpr>(1, 1, 1);
    std::string result_1 = ast_printer(*one);
    std::cout << result_1;

    

    return 0;
}

