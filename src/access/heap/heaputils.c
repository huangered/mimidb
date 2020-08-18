#include "access/heap.h"
#include "util/mctx.h"

// internal methods
HeapTuple _heap_buildtuple(int key, int value) {
    HeapTuple htup = palloc(sizeof(HeapTupleData));
    htup->key = key;
    htup->value = value;
    htup->len = sizeof(HeapTupleData);
    htup->xmax = 0;
    htup->xmin = 0;
    htup->ctid = 0;
    return htup;
}