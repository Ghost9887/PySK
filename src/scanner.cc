#include "scanner.h"

Scanner::Scanner(const std::string source) :
    source(source), start(0), current(0), line(1), tokens() {}

std::vector<Token> Scanner::tokenize() {
    while (!is_at_end()) {
        start = current;
        char c = peek();
        switch (c) {
            case '(': make_token(T_LPAREN); break; 
            case ')': make_token(T_RPAREN); break;
            case '{': make_token(T_LBRACE); break;
            case '}': make_token(T_RBRACE); break;
            case '.': make_token(T_DOT); break;
            case ',': make_token(T_COMMA); break;
            case '+': make_token(T_PLUS); break;
            case '-': make_token(T_MINUS); break;
            case '/': make_token(T_SLASH); break;
            case '*': make_token(T_STAR); break;
            case ';': make_token(T_SEMICOLON); break;
            case '"': string(); break;
            case '!': make_token(match('=') ? T_BANG_EQUAL : T_BANG); break;
            case '=': make_token(match('=') ? T_EQUAL_EQUAL : T_EQUAL); break;
            case '<': make_token(match('=') ? T_LESS_EQUAL : T_LESS); break;
            case '>': make_token(match('=') ? T_GREATER_EQUAL : T_GREATER); break;
            case ' ':
            case '\r':
            case '\t':
                break;
            case '\n':
                line++;
                break;
            default:
                if (is_digit(c)) {
                    number();
                    continue;
                }else if (is_alpha(c)) {
                    identifier();
                    continue;
                }
                std::cout << "Unexpected characater." << '\n';
        }
        advance();
    }

    return tokens;
}

void Scanner::identifier() {
    while (!is_at_end() && is_alpha_numeric(peek_next())) advance();
    std::string identifier = source.substr(start, current - start);   
    if (keywords_map.find(identifier) == keywords_map.end()) {
        make_token(T_IDENTIFIER);
    }else {
        make_token(keywords_map.at(identifier));
    }
}

void Scanner::string() {
    advance();
    start = current;
    while (!is_at_end() && peek_next() != '"') advance();
    if (is_at_end()) {
        std::cout << "Unterminated string." << '\n';
        return;
    }
    make_token(T_STRING);
}

void Scanner::number() {
    while (!is_at_end() && is_digit(peek_next())) advance();

    if (!is_at_end() && peek() == '.' && is_digit(peek_next())) {
        advance();
        while (!is_at_end() && is_digit(peek())) advance();
    }
    
    make_token(T_NUMBER);
}

void Scanner::make_token(TokenType type) {
    advance();
    std::string lexeme = "";
    if (current > start) {
        lexeme += source.substr(start, current - start);
    }else {
        lexeme += peek();
    }
    tokens.emplace_back(Token(type, lexeme, line));
}



bool Scanner::is_alpha_numeric(char c) {
    return is_digit(c) || is_alpha(c);
}

bool Scanner::is_alpha(char c) {
    return ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           c == '_';
}

bool Scanner::is_digit(char c) {
    return '0' <= c && c <= '9';
}

void Scanner::advance() {
    current++;
}
    

char Scanner::peek() {
    return source.at(current);
}

char Scanner::peek_next() {
    if (current + 1 < source.length()) {
        return source.at(current + 1);
    }
    return '\0';
}

bool Scanner::match(char expected) {
    if (peek_next() == expected) {
        advance();
        return true;
    }
    return false;
}

bool Scanner::is_at_end() {
    return current >= source.length();
}
