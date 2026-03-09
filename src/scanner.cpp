#include "scanner.hpp"

Scanner::Scanner() : ip(0), line(1), content() {}
Scanner::Scanner(std::string content) : ip(0), line(1), content(content) {}

void Scanner::load(const char *file_name) {
    auto size = std::filesystem::file_size(file_name);
    content.assign(size, '\0');

    std::ifstream file(file_name);
    if (!file) {
        std::cout << "Unable to read file: " << file_name << '\n';
        exit(1);
    }

    file.read(&content[0], size);
    file.close();
}

void Scanner::tokenize() {
    while (!is_at_end()) {
        char c = content.at(ip);
        switch (c) {
            case ';':
                add_token(TokenType::EOS);
                break;
            case '+':
                add_token(TokenType::PLUS);
                break;
            case '-':
                add_token(TokenType::SUB);
                break;
            case '/':
                add_token(TokenType::SLASH);
                break;
            case '*':
                add_token(TokenType::STAR);
                break;
            case '(':
                add_token(TokenType::L_PAREN);
                break;
            case ')':
                add_token(TokenType::R_PAREN);
                break;
            case '{':
                add_token(TokenType::L_BRACKET);
                break;
            case '}':
                add_token(TokenType::R_BRACKET);
                break;
            case '=':
                if (expected_next('=')) {
                    add_token(TokenType::EQUALS_EQUALS);
                    advance();
                }
                else add_token(TokenType::EQUALS);
                break;
            case '>':
                if (expected_next('=')) { 
                    add_token(TokenType::GREATER_EQUALS);
                    advance();
                }
                else add_token(TokenType::GREATER);
                break;
            case '<':
                if (expected_next('=')) {
                    add_token(TokenType::LESSER_EQUALS);
                    advance();
                }
                else add_token(TokenType::LESSER);
                break;
            case '.':
                add_token(TokenType::DOT);
                break;
            case ',':
                add_token(TokenType::COMMA);
                break;
            case '"':
                parse_identifier();
                break;
            case '\n':
                line++;
                break;
            case '\t':
            case ' ':
                break;
            default: 
                if (is_number(c)) {
                    parse_number();
                    continue;
                }
                std::cout << "Invalid syntax: " << content.at(ip) << '\n';
                exit(1);
        }
        advance();
    }
}

bool Scanner::is_at_end() {
    return ip >= content.length() || content.at(ip) == '\0';
}

void Scanner::advance() {
    ip++;
}

std::optional<char> Scanner::peek() {
    if (!is_at_end()) {
        return content.at(ip);
    }
    return std::nullopt;
}

std::optional<char> Scanner::peek_next() {
    if (ip + 1 < content.length() || content.at(ip + 1) != '\0') {
        return content.at(ip + 1);
    }
    return std::nullopt;
}

bool Scanner::expected_next(char c) {
    if (ip + 1 < content.length()) {
        return content.at(ip + 1) == c;
    }
    return false;
}

bool Scanner::is_number(char c) {
    return '0' <= c && c <= '9';
}

void Scanner::parse_number() {
    std::string num = "";
    do {
        num += content.at(ip);
        advance();
    }while (!is_at_end() && is_number(content.at(ip)));

    add_token(TokenType::NUMBER, std::stoi(num));
}

void Scanner::parse_identifier() {
    std::string identifier = "";
    identifier += '"';
    advance();

    while (peek().has_value() && peek().value() != '"') {
        identifier += content.at(ip);
        advance();
    }

    if (peek().has_value() && peek().value() == '"') {
        identifier += '"';
        add_token(TokenType::IDENTIFIER, identifier);
    }else {
        std::cout << "Unterminated string" << '\n';
        exit(1);
    }
}

void Scanner::add_token(TokenType type, int value) {
    tokens.emplace_back(Token(type, std::to_string(value), value, line));
}

void Scanner::add_token(TokenType type, std::string value) {
    tokens.emplace_back(Token(type, value, value, line));
}

void Scanner::add_token(TokenType type) {
    tokens.emplace_back(Token(type, "", std::nullopt, line));
}

void Scanner::print_tokens() {
    for (Token token : tokens) {
        token.print();
    }
    std::cout << '\n';
}
