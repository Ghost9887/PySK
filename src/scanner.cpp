#include "scanner.hpp"

Scanner::Scanner() : ip(0), content() {}
Scanner::Scanner(std::string content) : ip(0), content(content) {}

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
        switch (content.at(ip)) {
            case ';':
                add_token(EOS);
                break;
            case '+':
                add_token(Add);
                break;
            case '-':
                add_token(Sub);
                break;
            case '/':
                add_token(Divide);
                break;
            case '*':
                add_token(Multiply);
                break;
            case '(':
                add_token(LParen);
                break;
            case ')':
                add_token(RParen);
                break;
            case '{':
                add_token(LBracket);
                break;
            case '}':
                add_token(RBracket);
                break;
            case '=':
                add_token(Equals);
                break;
            case '>':
                add_token(Greater);
                break;
            case '<':
                add_token(Lesser);
                break;
            case '.':
                add_token(Dot);
                break;
            case ',':
                add_token(Comma);
                break;
            case '\n':
            case '\t':
            case ' ':
                break;
            default: 
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

void Scanner::add_token(Token token, std::string value) {}
void Scanner::add_token(Token token, int value) {}
void Scanner::add_token(Token token) {
    tokens.push_back(token);
}

void Scanner::print_tokens() {
    for (Token token : tokens) {
        std::cout << "[" << lookup_table.at(token) << "] ";
    }
    std::cout << '\n';
}
