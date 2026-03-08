#include "scanner.hpp"

Scanner::Scanner() : ip(0), content() {}

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
    std::cout << content;
}

void Scanner::tokenize() {
    switch (content.at(ip)) {
        default: 
            std::cout << "Invalid syntax: " << content.at(ip) << '\n';
            exit(1);
    }
}

void Scanner::advance() {
    if (ip < content.length() && content.at(ip) != '\0') {
        ip++;
    }
}
