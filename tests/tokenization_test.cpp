#include <catch2/catch_test_macros.hpp>
#include "common.hpp"
#include "scanner.hpp"

TEST_CASE("Tokenization test")
{
    std::string input = "(){}\nhello 32 ak\ntrieda"; 
    std::string expected_output = 
        "[LParen, 1][RParen, 1]"
        "[LBracket, 1][RBracket, 1][Identifier, hello, 2]"
        "[Number, 32, 2][Ak, 2][Trieda, 3]";
    
    Scanner scanner(input);
    scanner.tokenize();

    REQUIRE(expected_output == scanner.get_output());
}
