#include "values.h"

Value::Value(LiteralValue literal) :
    literal(literal) {}

int Values::write_value(LiteralValue literal) {
    values.emplace_back(Value(literal));
    return values.size() - 1;
}
