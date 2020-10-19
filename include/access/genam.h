/*
 * general index api function
 */
#ifndef _GENAM_H_
#define _GENAM_H_

#include "access/heaptuple.h"
#include "access/rel.h"
#include "access/scankey.h"

typedef struct SystemTableScanData {
    int i;
} SystemTableScanData;

typedef struct SystemTableScanData* SystemTableScan;

extern SystemTableScan systable_beginscan(Relation sysrelation, int nkeys, ScanKey key);
extern HeapTuple systable_getnext(SystemTableScan scan);
extern void systable_endscan(SystemTableScan scan);

#endif // !_GENAM_H_
