#ifndef VALUES_H
#define VALUES_H

#include <vector>

using Value = double;

class Values {
public:
    Values() = default;
    ~Values() = default;
    int write_value(Value value);
public:
    std::vector<Value> values;
};

#endif
