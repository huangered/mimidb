#include "access/amapi.h"
#include "access/genam.h"
#include "access/rel.h"
#include "access/relcache.h"
#include "access/scankey.h"
#include "access/heap.h"
// temp solution
#include "access/btree.h"

IndexAm*
GetIndexAmRoutine(Oid amhandler) {
    return (IndexAm*)bthandler();
}

SysTableScan
systable_beginscan(Relation heapRel, int nkeys, ScanKey key) {
    SysTableScan sysscan;

    sysscan            = (SysTableScan)palloc0(sizeof(struct SysTableScanData));
    sysscan->heap_rel  = heapRel;
    sysscan->heap_scan = heap_beginscan(heapRel, nkeys, key);
    return sysscan;
};

HeapTuple
systable_getnext(SysTableScan scan) {
    HeapTuple htup = heap_getnext(scan->heap_scan, Forward);
    return htup;
};

void
systable_endscan(SysTableScan scan) {
    heap_endscan(scan->heap_scan);
    pfree(scan);
};
