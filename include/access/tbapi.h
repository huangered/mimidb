#ifndef _table_api_h_
#define _table_api_h_

#include "storage/buf.h"

typedef struct HeapScanDescData {
    Relation rel;

    BlockNum num_blocks;    /* max block to scan */

    bool inited;        /* false = scan not init'd yet */
    BlockNum cblock;    /* current block # in scan */
    Buffer cbuf;        /* current buf # in scan */
    int key;
    int* value;
    int num_value;
} HeapScanDescData;

typedef HeapScanDescData* HeapScanDesc;




typedef struct TableAmRoute {
    void (*buildempty)(Relation rel);
    bool (*tuple_insert)(Relation rel, int key, int value);
    bool (*tuple_remove)(Relation rel, int key);
    bool (*gettuple)(HeapScanDesc scan);
} TableAmRoute;

TableAmRoute* table_route();

#endif // !_table_api_h_
