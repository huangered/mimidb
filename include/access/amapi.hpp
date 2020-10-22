#ifndef _amapi_h_
#define _amapi_h_

#include "mimi.hpp"
#include "access/relcache.hpp"
#include "storage/block.hpp"
#include "access/offset.hpp"

typedef struct IndexScanDescData {
    Relation index_rel;
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