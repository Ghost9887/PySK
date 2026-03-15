#include "scanner.h"


//TODO: REDO THIS COMPLETETLY

Scanner::Scanner(const std::string source) :
    source(source), start(0), current(0), line(1) {}

Token Scanner::scan_token() {
    start = current;
    if (is_at_end()) return make_token(TOKEN_EOF);

    char c = advance();
    if (is_alpha(c)) return identifier();
    if (is_digit(c)) return number();
    switch (c) {
        case '(': return make_token(TOKEN_LEFT_PAREN);
        case ')': return make_token(TOKEN_RIGHT_PAREN);
        case '{': return make_token(TOKEN_LEFT_BRACE);
        case '}': return make_token(TOKEN_RIGHT_BRACE);
        case ';': return make_token(TOKEN_SEMICOLON);
        case ',': return make_token(TOKEN_COMMA);
        case '.': return make_token(TOKEN_DOT);
        case '-': return make_token(TOKEN_MINUS);
        case '+': return make_token(TOKEN_PLUS);
        case '*': return make_token(TOKEN_STAR);
        case '/': return make_token(TOKEN_SLASH);
        case '!': return make_token(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
        case '=': return make_token(match('=') ? TOKEN_EQUAL_EQUAL: TOKEN_EQUAL);
        case '<': return make_token(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
        case '>': return make_token(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
        case '"': return string();
        case '\n': 
            line++;
            break;
        default: return error_token("Unexepected character."); 
    }
}

bool Scanner::is_at_end() {
    return current >= source.length();
}

bool Scanner::is_alpha(char c) {
    return ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           (c == '_');
}

bool Scanner::is_digit(char c) {
    return '0' <= c && c <= '9';
}

Token Scanner::make_token(TokenType type) {
    std::string lexeme = source.substr(start, current - start);
    Token token(type, lexeme, line);
    return token;
}

Token Scanner::error_token(std::string message) {
    Token token(TOKEN_ERROR, message, line);
    return token;
}

char Scanner::advance() {
    current++;
    return source.at(current - 1);
}

bool Scanner::match(char expected) {
    if (expected != peek_next()) return false;
    current++;
    return true;
}

char Scanner::peek() {
    return source.at(current);
}

char Scanner::peek_next() {
    if (current >= source.length()) return '\0';
    return source.at(current);
}

void Scanner::skip_whitespace() {
    while (true) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '/':
                if (peek_next() == '/') {
                    while (!is_at_end() && peek() != '\n') advance();
                }else {
                    return;
                }
                break;
            case '\n':
                line++;
                advance();
                break;
            default:
                return;
        }
    }
}

Token Scanner::string() {
    while (!is_at_end() && peek() != '"') {
        if (peek() == '\n') line++;
        advance();
    }

    if (is_at_end()) return error_token("Unterminated string.");

    advance();
    return make_token(TOKEN_STRING);
}

Token Scanner::number() {
    while(!is_at_end() && is_digit(peek())) advance();
    
    if (is_at_end()) return make_token(TOKEN_NUMBER);

    if (peek() == '.' && is_digit(peek_next())) {
        advance();

        while(!is_at_end() && is_digit(peek())) advance();
    }

    return make_token(TOKEN_NUMBER);
}

Token Scanner::identifier() {
    while(!is_at_end() && (is_alpha(peek()) || is_digit(peek()))) advance();
    return make_token(identifier_type());
}

TokenType Scanner::identifier_type() {
    std::string identifier = source.substr(start, current - start);
    if (keywords_map.find(identifier) != keywords_map.end()) {
        return keywords_map.at(identifier); 
    }
    return TOKEN_IDENTIFIER;
}
