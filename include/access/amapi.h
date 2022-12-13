/*
 * define all index access methods.
 */
#ifndef _amapi_hpp_
#define _amapi_hpp_

#include "mimi.h"
#include "access/relcache.h"
#include "access/offset.h"
#include "access/scan.h"
#include "access/scankey.h"
#include "storage/block.h"

struct IndexScanDescData {
    /* scan 参数 */
    Relation heap_rel;
    Relation index_rel;
    int nkeys;
    ScanKey skey;

    int key;
    int value;
    BlockNumber block;
    OffsetNumber offset;
};

typedef IndexScanDescData* IndexScanDesc;

class IndexAm {
public:
    virtual void BuildEmpty(Relation rel)                                  = 0;
    virtual bool Insert(Relation rel, int nkey, int ht_id)                 = 0;
    virtual bool Remove(Relation rel, int nkey)                            = 0;
    virtual IndexScanDesc BeginScan(Relation nrel, int nkeys, ScanKey key) = 0;
    virtual bool GetNext(IndexScanDesc scan, ScanDirection dir)            = 0;
    virtual void EndScan(Relation rel, int nkeys)                          = 0;
    virtual void Vacuum(Relation rel)                                      = 0;
};

#endif
