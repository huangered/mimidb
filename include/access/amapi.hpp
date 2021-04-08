#ifndef _amapi_h_
#define _amapi_h_

#include "mimi.hpp"
#include "access/relcache.hpp"
#include "storage/block.hpp"
#include "access/offset.hpp"
#include "access/scankey.hpp"

typedef struct IndexScanDescData {
    Relation index_rel;
    int key;
    int value;
    BlockNumber block;
    OffsetNumber offset;
} IndexScanDescData;

typedef IndexScanDescData* IndexScanDesc;

class IndexAm {
public:
    virtual void BuildEmpty(Relation rel) = 0;
    virtual bool Insert(Relation rel, int nkey, int ht_id) = 0;
    virtual bool Remove(Relation rel, int nkey) = 0;
    virtual IndexScanDesc BeginScan(Relation nrel, int nkeys, ScanKey key) = 0;
    virtual void EndScan(Relation rel, int nkeys) = 0;
    virtual bool GetTuple(IndexScanDesc scan) = 0;
    virtual void Vacuum(Relation rel) = 0;
};

#endif