#include "access/btree.h"
#include "util/builtins.h"

Datum intcmp(FunctionCallInfo fcinfo) {
    int a = fcinfo->args[0];
    int b = fcinfo->args[1];

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