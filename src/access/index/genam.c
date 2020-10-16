#include "access/genam.h"
#include "access/relcache.h"
#include "access/scankey.h"

SystemTableScan
systable_beginscan(Relation sysrelation, int nkeys, ScanKey key) {
    return NULL; 
};

HeapTuple
systable_getnext(SystemTableScan scan) {
    return NULL;
};

void
systable_endscan(SystemTableScan scan) {
};
