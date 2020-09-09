#ifndef _scankey_h_
#define _scankey_h_

#include "mimi.h"
#include "access/strategynumber.h"
#include "util/fmgr.h"

typedef struct ScanKeyData {
    Datum sk_data;
    FmgrInfo sk_func;
    StrategyNumber sk_number;

} ScanKeyData;

typedef ScanKeyData* ScanKey;

#endif // !_scankey_h_

