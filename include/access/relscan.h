/*
 *表扫描描述定义
 */
#ifndef _relscan_h_
#define _relscan_h_

#include "access/genam.h"
#include "access/indextuple.h"


// 堆表扫描描述
typedef struct HeapScanDescData {
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
    HeapTupleData rs_curtuple; // 当前tuple
    BlockNumber rs_curblock;   // 当前block
    Buffer rs_curbuf;          // 当前buf
} HeapScanDescData;

typedef struct IndexScanDescData {
    /* scan 参数 */
    Relation heap_rel;  /*heap表描述符*/
    Relation index_rel; /*index表描述符*/
    int nkeys;
    ScanKey keyData;
    ScanKey orderByData;

    // index-only 扫描
    IndexTuple xs_itup;
    TupleDesc xs_itupdesc;
    HeapTuple xs_hitup;
    TupleDesc xs_hitupdesc;

    int key;
    int value;
    BlockNumber block;
    OffsetNumber offset;
} IndexScanDescData;

#endif