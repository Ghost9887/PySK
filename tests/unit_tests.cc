#include "catch2/catch_test_macros.hpp"
#include <fstream>
#include <vector>
#include <sstream>
#include "scanner.h"

TEST_CASE("Tokenize") {
    std::string source;
    std::fstream file("../tests/token_test1.psk");
    std::stringstream buffer;
    buffer << file.rdbuf();
    source = buffer.str();

    Scanner scanner(source);
    std::vector<Token> tokens = scanner.tokenize();
    std::vector<Token> expected_tokens;
    expected_tokens.emplace_back(Token(T_LPAREN, "(", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_RPAREN, ")", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_LBRACE, "{", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_RBRACE, "}", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_COMMA, ",", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_DOT, ".", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_GREATER, ">", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_GREATER_EQUAL, ">=", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_EQUAL_EQUAL, "==", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_LESS_EQUAL, "<=", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_LESS, "<", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_BANG, "!", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_BANG_EQUAL, "!=", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_EQUAL, "=", 1, std::monostate()));
    expected_tokens.emplace_back(Token(T_IDENTIFIER, "identifier", 2, std::monostate()));
    expected_tokens.emplace_back(Token(T_NUMBER, "30", 3, 30.0));
    expected_tokens.emplace_back(Token(T_NUMBER, "30.5", 4, 30.5));
    expected_tokens.emplace_back(Token(T_STRING, "Hello, World!", 5, "Hello, World!"));
    expected_tokens.emplace_back(Token(T_TRIEDA, "trieda", 6, std::monostate()));
    expected_tokens.emplace_back(Token(T_AK, "ak", 6, std::monostate()));
    expected_tokens.emplace_back(Token(T_FUNK, "funk", 6, std::monostate()));
    expected_tokens.emplace_back(Token(T_INAK, "inak", 6, std::monostate()));
    expected_tokens.emplace_back(Token(T_VYTLAC, "vytlac", 6, std::monostate()));

    REQUIRE(tokens == expected_tokens);
}
