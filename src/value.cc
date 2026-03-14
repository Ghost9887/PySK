#include "value.h"

void Values::write_value(Value value) {
    values.push_back(value);
}

void Values::print_value(Value value) {
    std::cout << value;
}
