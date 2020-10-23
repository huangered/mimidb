#ifndef _amapi_h_
#define _amapi_h_

#include "mimi.h"
#include "access/relcache.h"
#include "access/scan.h"
#include "storage/block.h"
#include "access/offset.h"

typedef struct IndexScanDescData {
    TableScanDescData rs_base;  // 继承 tableScanDescData;

    int key;
    int value;
    BlockNumber block;
    OffsetNumber offset;
} IndexScanDescData;

typedef IndexScanDescData* IndexScanDesc;

typedef struct IndexAmRoute {
    void (*ambuildempty)(Relation rel);
    bool (*aminsert)(Relation rel, int key, int ht_id);
    bool (*amremove)(Relation rel, int key);
    bool (*amgettuple)(IndexScanDesc scan);
    void (*amvacuum)(Relation rel);
} IndexAmRoute;

extern IndexAmRoute* buildRoute();

#endif