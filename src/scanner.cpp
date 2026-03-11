#include "scanner.h"

Scanner::Scanner(std::string content) :
    content(content), tokens(), start(0), current(0), line(1) {}

std::vector<Token> Scanner::scan_tokens() {
    while (!is_at_end()) {
        start = current;
        scan_token();
    }

    current++;
    tokens.emplace_back(Token(TokenType::_EOF, "", std::monostate{}, line, current));
    
    return tokens;
}

void Scanner::scan_token() {
    char c = advance();
    switch (c) {
        case '(':
            add_token(TokenType::L_PAREN);
            break;
        case ')':
            add_token(TokenType::R_PAREN);
            break;
        case '{':
            add_token(TokenType::L_BRACE);
            break;
        case '}':
            add_token(TokenType::R_BRACE);
            break;
        case ',':
            add_token(TokenType::COMMA);
            break;
        case '.':
            add_token(TokenType::DOT);
            break;
        case '-':
            add_token(TokenType::MINUS);
            break;
        case '+':
            add_token(TokenType::PLUS);
            break;
        case '%':
            add_token(TokenType::PERCENT);
            break;
        case ';':
            add_token(TokenType::SEMICOLON);
            break;
        case '*':
            add_token(TokenType::STAR);
            break;
        case '!':
            add_token(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            add_token(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '>':
            add_token(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '<':
            add_token(match('=') ? TokenType::LESSER_EQUAL : TokenType:: LESSER);
            break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !is_at_end()) advance();
            }else {
                add_token(TokenType::SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n':
            line++;
            break;
        case '"':
            string();
            break;
        default:
            if (is_digit(c)) {
                number();
                break;
            }else if (is_alpha(c)) {
                identifier();
                break;
            }else {
                Dio::error(line, current, "Unexpected character.");
                break;
            }
    }
}

bool Scanner::is_at_end() {
    return current >= content.length();
}

char Scanner::advance() {
    current++;
    return content.at(current - 1);
}

void Scanner::add_token(TokenType type) {
    add_token(type, std::monostate{});
}

void Scanner::add_token(TokenType type, LiteralValue literal) {
    std::string text = content.substr(start, current - start);
    tokens.emplace_back(Token(type, text, literal, line, current));
}

bool Scanner::match(const char c) {
    if (is_at_end()) return false;
    if (content.at(current) != c) return false; 

    current++;
    return true;
}

char Scanner::peek() {
    if (is_at_end()) return '\0';
    return content.at(current);
}

char Scanner::peek_next() {
    if (current + 1 < content.length()) {
        return content.at(current + 1);
    }else return '\0';
}

void Scanner::string() {
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (is_at_end()) {
        Dio::error(line, current, "Unterminated string.");
        return;
    }

    advance();
    std::string value = content.substr(start + 1, current - start + 1);
    add_token(TokenType::STRING, value);
}

bool Scanner::is_digit(const char c) {
    return '0' <= c && c <= '9';
}

void Scanner::number() {
    bool decimal = false;
    while (is_digit(peek())) advance();

    if (peek() == '.' && is_digit(peek_next())) {
        decimal = true;
        advance();
        while (is_digit(peek())) advance();
    }
    std::string num = content.substr(start, current - start);

    add_token(TokenType::NUMBER, decimal ? std::stof(num) : std::stoi(num));
}


bool Scanner::is_alpha(const char c) {
    return     ('a' <= c && c <= 'z')
            || ('A' <= c && c <= 'Z')
            || (c == '_');
}

bool Scanner::is_alphanumeric(const char c) {
    return is_digit(c) || is_alpha(c);
}

void Scanner::identifier() {
    while (is_alphanumeric(peek())) advance();

    std::string identifier = content.substr(start, current - start);
    if (keywords_map.find(identifier) != keywords_map.end()) {
        add_token(keywords_map.at(identifier));
    }else {
        add_token(TokenType::IDENTIFIER);
    }
}
