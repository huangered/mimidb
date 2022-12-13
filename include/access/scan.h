/*
 * relation scan descriptor definitions.
 */
#ifndef _scan_hpp_
#define _scan_hpp_

#include "access/relation.h"
#include "access/scankey.h"
#include "storage/block.h"
#include "storage/buf.h"

// 堆表扫描描述
struct HeapScanDescData {
    /* scan parameter */
    Relation rs_rd; // 表描述符
    int rs_nkeys;   // scan key 个数
    ScanKey rs_key; // scan key 的指针

    /* initscan初始化设定值 */
    BlockNumber rs_nblocks;    // rel 总共 block 数量
    BlockNumber rs_startblock; // rel 开始 block number
    BlockNumber rs_numblocks;  // rel 最大扫描数量

    /* scan 当前状态 */
    bool rs_inited;            // scan是否初始化
    struct HeapTupleData rs_curtuple; // 当前tuple
    BlockNumber rs_curblock;   // 当前block
    Buffer rs_curbuf;          // 当前buf
};

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
