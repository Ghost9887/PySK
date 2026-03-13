#include "environment.h"

Environment::Environment() :
    enclosing(nullptr) {}

Environment::Environment(std::shared_ptr<Environment> environment) :
    enclosing(environment) {}

void Environment::define(Token &name, LiteralValue value) {
    if (values.find(name.lexeme) != values.end()) {
        throw RuntimeError(name, "Premena uz existuje.");
    }

    if (enclosing && enclosing->exists(name.lexeme)) {
        throw RuntimeError(name, "Premena uz existuje.");
    }

    values.emplace(name.lexeme, value);
}

LiteralValue Environment::get(Token &name) {
    if (values.find(name.lexeme) != values.end()) {
        return values.at(name.lexeme);
    }else if (enclosing) {
        return enclosing->get(name);
    }
    throw RuntimeError(name, "Premena neexistuje.");
}

void Environment::assign(Token &name, LiteralValue value) {
    if (values.find(name.lexeme) == values.end()) {
        if (enclosing){
            enclosing->assign(name, value);
            return;
        }else {
            throw RuntimeError(name, "Premena neexistuje.");
        }
    }else {
        values.at(name.lexeme) = value;
    }
}

bool Environment::exists(const std::string& name) {
    if (values.find(name) != values.end()) return true;
    if (enclosing) return enclosing->exists(name);
    return false;
}
