#ifndef _HEAP_H_
#define _HEAP_H_

#include "mimi.h"
#include "rel.h"
#include "storage/bufmgr.h"

typedef struct HeapTupleData {
    int len;
    int xmin;
    int xmax;
    int ctid;
    int tag;
    int key;
    int value;
} HeapTupleData;

typedef HeapTupleData* HeapTuple;

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

extern void heapbuildempty(Relation rel);
extern bool heapinsert(Relation rel, int key, int value);
extern bool heapremove(Relation rel, int key);
extern bool heapgettuple(HeapScanDesc scan);

// internal methods
HeapTuple _heap_buildtuple(int key, int value);

Buffer GetBufferForTuple(Relation rel, Size len);
void RelationPutHeapTuple(Relation rel, Buffer buf, HeapTuple htup);

// for debug
void print_heap(Relation rel);


#endif // !_HEAP_H_
