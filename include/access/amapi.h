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

typedef struct IndexScanDescData* IndexScanDesc;

     void BuildEmpty(Relation rel);
    
 bool Insert(Relation rel, int nkey, int ht_id);
     bool Remove(Relation rel, int nkey);
 IndexScanDesc BeginScan(Relation nrel, int nkeys, ScanKey key);
     bool GetNext(IndexScanDesc scan,enum ScanDirection dir);
 void EndScan(Relation rel, int nkeys);
     void Vacuum(Relation rel);


#endif
