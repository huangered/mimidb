#include "access/genam.hpp"
#include "access/rel.hpp"
#include "access/relcache.hpp"
#include "access/scankey.hpp"
#include "util/mctx.hpp"
#include "access/heap.hpp"

SysTableScanDesc
systable_beginscan(Relation heapRel, int nkeys, ScanKey key) {
    SysTableScanDesc sysscan;

    sysscan = (SysTableScanDesc)palloc0(sizeof(SysTableScanDescData));
    sysscan->heap_rel = heapRel;
    sysscan->heap_scan = heapRel->tb_am->BeginScan(heapRel, nkeys, key);
    return sysscan;
};

HeapTuple
systable_getnext(SysTableScanDesc scan) {
    HeapTuple htup = scan->heap_rel->tb_am->GetNext(scan->heap_scan, ScanDirection::Forward);
    return htup;
};

void
systable_endscan(SysTableScanDesc scan) {
    scan->heap_rel->tb_am->EndScan(scan->heap_scan);
    pfree(scan);
};
