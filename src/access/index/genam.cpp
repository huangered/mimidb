#include "access/genam.hpp"
#include "access/rel.hpp"
#include "access/relcache.hpp"
#include "access/scankey.hpp"
#include "access/heap.hpp"

SysTableScan
systable_beginscan(Relation heapRel, int nkeys, ScanKey key) {
    SysTableScan sysscan;

    sysscan            = (SysTableScan)palloc0(sizeof(SysTableScanData));
    sysscan->heap_rel  = heapRel;
    sysscan->heap_scan = heap_beginscan(heapRel, nkeys, key);
    return sysscan;
};

HeapTuple
systable_getnext(SysTableScan scan) {
    HeapTuple htup = heap_getnext(scan->heap_scan, ScanDirection::Forward);
    return htup;
};

void
systable_endscan(SysTableScan scan) {
    heap_endscan(scan->heap_scan);
    pfree(scan);
};
