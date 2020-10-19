#ifndef _table_api_h_
#define _table_api_h_

#include "storage/buf.h"
#include "executor/tuptable.h"
#include "access/offset.h"
#include "access/heaptuple.h"
#include "access/scankey.h"

typedef struct HeapScanDescData {
    Relation rel;

    BlockNumber num_blocks;    /* max block to scan */

    bool inited;        /* false = scan not init'd yet */
    BlockNumber cblock;    /* current block # in scan */
    Buffer cbuf;        /* current buf # in scan */
    OffsetNumber offset; /* current offset # in scan */
    int key;
    int value;
} HeapScanDescData;

typedef HeapScanDescData* HeapScanDesc;

typedef struct TableAmRoute {
    void (*buildempty)(Relation rel);
    bool (*tuple_insert)(Relation rel, TupleSlotDesc *slot);
    bool (*tuple_remove)(Relation rel, int key);
    bool (*gettuple)(HeapScanDesc scan);
    HeapScanDesc (*beginscan)(Relation rel, int nkeys, ScanKey keys);
    HeapTuple (*getnext)(HeapScanDesc scan);
    bool (*endscan)(HeapScanDesc scan);
    void (*vacuum)(Relation rel);
} TableAmRoute;

TableAmRoute* table_route();

#endif // !_table_api_h_
