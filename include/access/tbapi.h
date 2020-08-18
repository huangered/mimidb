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


typedef void (*buildempty)(Relation);
typedef bool (*insert)(Relation, int, int);
typedef bool (*hremove)(Relation, int);
typedef bool (*gettuple)(HeapScanDesc);

typedef struct TableAmRoute {
    buildempty buildempty;
    insert insert;
    hremove remove;
    gettuple gettuple;
} TableAmRoute;

TableAmRoute* table_route();

#endif // !_table_api_h_
