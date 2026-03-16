#include "values.h"

int Values::write_value(Value value) {
    values.push_back(value);
    return values.size() - 1;
}
