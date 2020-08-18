#ifndef _amapi_h_
#define _amapi_h_

#include "mimi.h"
#include "access/relcache.h"
#include "storage/block.h"
#include "access/offset.h"

typedef struct IndexScanDescData {
    Relation index_rel;
    int key;
    int value;
    BlockNum block;
    OffsetNumber offset;
} IndexScanDescData;

typedef IndexScanDescData* IndexScanDesc;

typedef void (*Buildempty)(Relation rel);
typedef bool (*Insert)(Relation rel, int key, int value);
typedef bool (*Remove)(Relation rel, int key);
typedef bool (*Gettuple)(IndexScanDesc scan);
typedef void (*Vacuum)(Relation rel);

typedef struct IndexAmRoute {
    Buildempty buildempty;
    Insert insert;
    Remove remove;
    Gettuple gettuple;
    Vacuum vacuum;
} IndexAmRoute;

extern IndexAmRoute* buildRoute();

#endif