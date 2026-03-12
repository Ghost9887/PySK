#include "environment.h"

void Environment::define(Token name, LiteralValue value) {
    if (values.find(name.lexeme) != values.end()) {
        throw RuntimeError(name, "Premena uz existuje.");
    }else {
        values.emplace(name.lexeme, value);
    }
}

LiteralValue Environment::get(Token name) {
    if (values.find(name.lexeme) != values.end()) {
        return values.at(name.lexeme);
    }
    throw RuntimeError(name, "Premena neexistuje.");
}

void Environment::assign(Token name, LiteralValue value) {
    if (values.find(name.lexeme) == values.end()) {
        throw RuntimeError(name, "Premena neexistuje.");
    }
    values.at(name.lexeme) = value;
}
