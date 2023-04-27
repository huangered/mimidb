/*
 * general index api function
 */
#ifndef _genam_h_
#define _genam_h_

#include "access/rel.h"
#include "access/scankey.h"
#include "access/scan.h"

/*
 * ambuild 的返回统计
 */
typedef struct IndexBuildResult {
    double heap_tuples;  /* 父表中的 tuple 数 */
    double index_tuples; /* 插入的 tuple 数 */
} IndexBuildResult;

typedef struct IndexScanDescData* IndexScanDesc;
typedef struct SysScanDescData* SysScanDesc;

typedef enum IndexUniqueCheck {
    UNIQUE_CHECK_NO,       /* 不做 unique 检查 */
    UNIQUE_CHECK_YES,      /* 插入时检查 unique */
    UNIQUE_CHECK_EXISTING, /* 检查是否有存在的tuple */
} IndexUniqueCheck;

/*
 * indexam.c 通用index方法
 */
extern Relation index_open(Oid relationId);
extern void index_close(Relation relation);

/*
 * heap 或 index 接口 访问 system catalog (genam.c）
 */
extern SysTableScan systable_beginscan(Relation sysrelation, int nkeys, ScanKey key);
extern HeapTuple systable_getnext(SysTableScan scan);
extern void systable_endscan(SysTableScan scan);

#endif // !_GENAM_H_
