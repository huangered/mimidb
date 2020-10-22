#include "access/genam.hpp"
#include "access/relcache.hpp"
#include "access/scankey.hpp"

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
