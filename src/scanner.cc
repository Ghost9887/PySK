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
            case '!':
                if (match('=')) {
                    advance();
                    make_token(T_BANG_EQUAL);
                    continue;
                }
                make_token(T_BANG);
                break;
            case '=':
                if (match('=')) {
                    advance();
                    make_token(T_EQUAL_EQUAL);
                    continue;
                }
                make_token(T_EQUAL);
                break;
            case '<':
                if (match('=')) {
                    advance();
                    make_token(T_LESS_EQUAL);
                    continue;
                }
                make_token(T_LESS);
                break;
            case '>':
                if (match('=')) {
                    advance();
                    make_token(T_GREATER_EQUAL);
                    continue;
                }
                make_token(T_GREATER);
                break;
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
    while (!is_at_end() && is_alpha_numeric(peek())) advance();
    std::string identifier = source.substr(start, current - start);   
    if (keywords_map.find(identifier) == keywords_map.end()) {
        make_token(T_IDENTIFIER);
    }else {
        TokenType type = keywords_map.at(identifier);

        if (type == T_PRAVDA) make_token(type, true);
        else if (type == T_NEPRAVDA) make_token(type, false);
        else make_token(type);
    }
}

void Scanner::string() {
    advance();
    start = current;
    while (!is_at_end() && peek() != '"') advance();
    if (is_at_end()) {
        std::cout << "Unterminated string." << '\n';
        return;
    }
    std::string str = source.substr(start, current - start);
    make_token(T_STRING, str);
}

void Scanner::number() {
    while (!is_at_end() && is_digit(peek())) advance();

    if (!is_at_end() && peek() == '.' && is_digit(peek_next())) {
        advance();
        while (!is_at_end() && is_digit(peek())) advance();
    }
    std::string lexeme = source.substr(start, current  - start);
    make_token(T_NUMBER, std::stod(lexeme));
}

void Scanner::make_token(TokenType type) {
    std::string lexeme = "";
    if (current > start) {
        lexeme += source.substr(start, current - start);
    }else {
        lexeme += peek();
    }
    tokens.emplace_back(Token(type, lexeme, line, std::monostate()));
}

void Scanner::make_token(TokenType type, LiteralValue literal) {
    std::string lexeme = "";
    lexeme += source.substr(start, current - start);
    tokens.emplace_back(Token(type, lexeme, line, literal));
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
