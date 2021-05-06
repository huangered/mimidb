#include "access/btree.hpp"
#include "util/builtins.hpp"


Datum
int8cmp(FunctionCallInfo fcinfo) {
    int8_t a = (int8_t)fcinfo->args[0];
    int8_t b = (int8_t)fcinfo->args[1];

    return a - b;
}


Datum
int16cmp(FunctionCallInfo fcinfo) {
    int16_t a = (int16_t)fcinfo->args[0];
    int16_t b = (int16_t)fcinfo->args[1];

    return a - b;
}

Datum
int32cmp(FunctionCallInfo fcinfo) {
    int32_t a = (int32_t)fcinfo->args[0];
    int32_t b = (int32_t)fcinfo->args[1];
    
    return a - b;
}