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
            case '"':
                parse_string();
                continue;
            case '/':
                expected_next('/') ? parse_comment() : add_token(TokenType::SLASH);
                break;
            case '=':
                expected_next('=') ? add_token(TokenType::EQUALS_EQUALS) : add_token(TokenType::EQUALS);
                break;
            case '>':
                expected_next('=') ? add_token(TokenType::GREATER_EQUALS) : add_token(TokenType::GREATER);
                break;
            case '<':
                expected_next('=') ? add_token(TokenType::LESSER_EQUALS) : add_token(TokenType::LESSER);
                break;
            case '!':
                expected_next('=') ? add_token(TokenType::NOT_EQUALS) : add_token(TokenType::NOT);
                break;
            case '.':
                add_token(TokenType::DOT);
                break;
            case ',':
                add_token(TokenType::COMMA);
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
                }else if (is_alphanumeric(c)) {
                    parse_identifier();
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
        if (content.at(ip + 1) == c) {
            advance();
            return true;
        }
    }
    return false;
}

bool Scanner::is_number(char c) {
    return '0' <= c && c <= '9';
}

bool Scanner::is_alphanumeric(char c) {
    return 
        is_number(c) 
        || ('a' <= c && c <= 'z') 
        || ('A' <= c && c <= 'Z')
        || (c == '_'); 
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
    do {
        identifier += content.at(ip);
        advance();
    } while(!is_at_end() && is_alphanumeric(content.at(ip)));

    if (keywords_table.find(identifier) != keywords_table.end()) {
        add_token(keywords_table.at(identifier));
    }else {
        add_token(TokenType::IDENTIFIER, identifier);
    }
}

void Scanner::parse_string() {
    std::string str = "";
    advance();
    while (!is_at_end() && peek().value() != '"') {
        if (peek() == '\n') line++;
        else str += peek().value();
        advance();
    }

    if (is_at_end()) {
        std::cout << "Unterminated string" << '\n';
        exit(1);
    }
    advance();
    add_token(TokenType::STRING, str);
}

void Scanner::parse_comment() {
    while(!is_at_end() && peek().value() != '\n') advance();
}

void Scanner::print_tokens() {
    std::string output = "";
    for (Token token : tokens) {
        output += token.to_string();
    }
    std::cout << output << '\n';
}

std::vector<Token> &Scanner::get_tokens() {
    return tokens;
}

std::string Scanner::get_output() {
    std::string output = "";
    for (Token token : tokens) {
        output += token.to_string();
    }
    return output;
}
