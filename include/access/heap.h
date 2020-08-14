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

extern void heapbuildempty(Relation rel);
extern bool heapinsert(Relation rel, int key, int value);
extern bool heapremove(Relation rel, int key);
extern bool heapgettuple(Relation rel, int key, int* value);

// internal methods
HeapTuple _heap_buildtuple(int key, int value);

Buffer GetBufferForTuple(Relation rel, Size len);
void RelationPutHeapTuple(Relation rel, Buffer buf, HeapTuple htup);


#endif // !_HEAP_H_
