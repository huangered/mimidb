/*
 * general index api function
 */
#ifndef _genam_hpp_
#define _genam_hpp_

#include "access/heaptuple.hpp"
#include "access/rel.hpp"
#include "access/scankey.hpp"

typedef struct SystemTableScanData {
    int i;
} SystemTableScanData;

typedef struct SystemTableScanData* SystemTableScan;

extern SystemTableScan systable_beginscan(Relation sysrelation, int nkeys, ScanKey key);
extern HeapTuple systable_getnext(SystemTableScan scan);
extern void systable_endscan(SystemTableScan scan);

#endif // !_GENAM_H_
