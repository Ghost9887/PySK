#ifndef VALUE_H
#define VALUE_H

#include "common.h"

using Value = double;

class Values {
public:
    Values() = default;
    ~Values() = default;
    void write_value(Value value);
    static void print_value(Value value);
public:
    std::vector<Value> values;
};

#endif
