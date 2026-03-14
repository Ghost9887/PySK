#include "return_value.h"

ReturnValue::ReturnValue(LiteralValue value) :
    std::runtime_error(""), value(value) {} 

