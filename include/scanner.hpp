#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "common.hpp"
#include "token.hpp"

class Scanner {
public:
    Scanner();
    Scanner(std::string content);
    ~Scanner() = default;
    void load(const char *file_name);
    void tokenize();
    void print_tokens();
    std::string get_output();
    std::vector<Token> &get_tokens();
private:
    std::vector<Token> tokens;
    std::string content;
    int ip;
    int line;
    void advance();
    std::optional<char> peek();
    std::optional<char> peek_next();
    bool expected_next(char c);
    bool is_at_end();
    bool is_number(char c);
    bool is_alphanumeric(char c);
    void parse_number();
    void parse_identifier();
    void parse_string();
    void parse_comment();

    template <typename T>
    void add_token(TokenType type, T value) {
        std::stringstream stream;
        stream << value;
        tokens.emplace_back(Token(type, stream.str(), value, line));
    }
    void add_token(TokenType type) {
        tokens.emplace_back(Token(type, "", std::nullopt, line));
    }
};

#endif
