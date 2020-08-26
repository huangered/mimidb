#ifndef _scankey_h_
#define _scankey_h_

#include "mimi.h"
#include "access/strategynumber.h"


typedef int (*cmp1)(Datum l, Datum r);

typedef struct ScanKeyData {
    Datum sk_data;
    cmp1 sk_comp;
    StrategyNumber sk_number;
} ScanKeyData;

typedef ScanKeyData* ScanKey;

static int int_cmp(Datum l, Datum r) {
    int i = (int)l;
    int j = (int)r;

    if (i == j) {
        return 0;
    }
    else if (i > j) {
        return 1;
    }
    else {
        return -1;
    }
}

#endif // !_scankey_h_

