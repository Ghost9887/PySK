#ifndef VALUES_H
#define VALUES_H

#include <vector>
#include <string>
#include <variant>

using LiteralValue = std::variant<std::monostate, std::string, double, bool>;

class Value {
public:
    Value(LiteralValue literal);
    ~Value() = default;
public:
    LiteralValue literal;
};

class Values {
public:
    Values() = default;
    ~Values() = default;
    int write_value(LiteralValue value);
public:
    std::vector<Value> values;
};

#endif
