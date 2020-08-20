#include "access/heap.h"
#include "util/mctx.h"

// internal methods
HeapTuple _heap_buildtuple(Relation rel, TupleSlotDesc* slot) {
    HeapTuple htup = palloc(sizeof(HeapTupleData));
    htup->key = slot->key;
    htup->value = slot->value;
    htup->len = sizeof(HeapTupleData);
    htup->xmax = 0;
    htup->xmin = 0;
    htup->ctid = 0;
    return htup;
}