#include "access/btree.h"
#include "util/builtins.h"

Datum int32cmp(FunctionCallInfo fcinfo) {
    int32_t a = fcinfo->args[0];
    int32_t b = fcinfo->args[1];
    
    if (a > b) {
        return (Datum)1;
    }
    else if (a == b) {
        return (Datum)0;
    }
    else {
        return (Datum)(-1);
    }
}