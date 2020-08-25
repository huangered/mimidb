#include "access/heap.h"
#include "util/mctx.h"

// internal methods
HeapTuple _heap_buildtuple(Relation rel, TupleSlotDesc* slot) {
    int data_size = 2 * sizeof(int);
    int len = sizeof(HeapTupleData) + sizeof(HeapTupleHeaderData) + data_size;
    HeapTuple htup = palloc(len);

    htup->t_len = data_size + sizeof(HeapTupleHeaderData);
    htup->t_data->t_hoff = sizeof(HeapTupleHeaderData);
    char* ptr = ((char*)htup + len);

    memcpy(ptr, &slot->key, 4);
    memcpy(ptr + 4, &slot->value, 4);

    return htup;
}