/*
 * general index api function
 */
#ifndef _GENAM_H_
#define _GENAM_H_

#include "access/heaptuple.h"

typedef struct SystemTableScanData {
    int i;
} SystemTableScanData;

typedef struct SystemTableScanData* SystemTableScan;

extern SystemTableScan systable_beginscan();
extern HeapTuple systable_getnext(SystemTableScan scan);
extern void systable_endscan(SystemTableScan scan);

#endif // !_GENAM_H_
