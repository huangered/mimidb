#include "access/heap.h"
#include "util/mctx.h"

// internal methods
HeapTuple _heap_buildtuple(Relation rel, TupleSlotDesc* slot) {
    HeapTupleHeader td;
    int hoff = sizeof(HeapTupleHeaderData);
    int data_size = 2 * sizeof(int);
    int len = HEAP_TUPLE_SIZE + hoff + data_size;
    HeapTuple htup = palloc(len);

    htup->t_len = data_size + hoff;
    htup->t_data = td = (HeapTupleHeader)((char*)htup + HEAP_TUPLE_SIZE);
    htup->t_data->t_hoff = hoff;

    // for simple, we only have (key,value) now.
    memcpy(((char*)td + hoff), &slot->key, sizeof(int));
    memcpy(((char*)td + hoff + sizeof(int)), &slot->value, sizeof(int));

    return htup;
}