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

class BaseIndex {
public:
    virtual void buildempty(Relation rel) = 0;
    virtual bool insert(Relation rel, int key, int ht_id) = 0;
    virtual bool remove(Relation rel, int key) = 0;
    virtual bool gettuple(IndexScanDesc scan) = 0;
    virtual void vacuum(Relation rel) = 0;
};

#endif