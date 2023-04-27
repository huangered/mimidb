/*
 * relation scan descriptor definitions.
 */
#ifndef _scan_hpp_
#define _scan_hpp_

#include "access/relation.h"
#include "access/scankey.h"
#include "storage/block.h"
#include "storage/buf.h"

typedef struct HeapScanDescData* HeapScanDesc;

// 索引表扫描描述
struct IndexScanDescData1 {
    /* scan parameter */
    Relation heapRelation;
    Relation indexRelation;

    int numberOfKeys;

    ScanKey keyData;
};

typedef struct IndexScanDescData1* IndexScanDesc1;

// 系统表扫描描述
struct SysTableScanData {
    Relation heap_rel;
    Relation index_rel;
    HeapScanDesc heap_scan;
    IndexScanDesc1 index_scan;
};

typedef struct SysTableScanData* SysTableScan;

enum ScanDirection {
    Backward,
    Forward
};

#endif
