#include "access/genam.hpp"
#include "access/rel.hpp"
#include "access/relcache.hpp"
#include "access/scankey.hpp"
#include "util/mctx.hpp"
#include "access/heap.hpp"

SysTableScan
systable_beginscan(Relation heapRel, int nkeys, ScanKey key) {
    SysTableScan sysscan;

    sysscan            = (SysTableScan)palloc0(sizeof(SysTableScanData));
    sysscan->heap_rel  = heapRel;
    sysscan->heap_scan = heapRel->tb_am->BeginScan(heapRel, nkeys, key);
    return sysscan;
};

HeapTuple
systable_getnext(SysTableScan scan) {
    HeapTuple htup = scan->heap_rel->tb_am->GetNext(scan->heap_scan, ScanDirection::Forward);
    return htup;
};

void
systable_endscan(SysTableScan scan) {
    scan->heap_rel->tb_am->EndScan(scan->heap_scan);
    pfree(scan);
};
