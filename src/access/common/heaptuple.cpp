#include "access/heaptuple.hpp"
#include "access/tupledesc.hpp"
#include "util/mctx.hpp"

HeapTuple
heap_form_tuple(TupleDesc tupdesc, Datum* values) {
    HeapTuple htup;
    HeapTupleHeader td;
    int data_size = 0;
    int natts = tupdesc->natts;
    for (int i = 0; i < natts; i++) {
        FormData_mimi_attribute attr = tupdesc->attr[i];
        data_size += attr.att_len;
    }

    size_t len = HEAP_TUPLE_SIZE + HEAP_TUPLE_HEADER_SIZE + data_size;

    htup = (HeapTuple)malloc(len);
    htup->t_len = data_size;
    htup->t_data = td = (HeapTupleHeader)((char*)htup + HEAP_TUPLE_SIZE);

    memcpy(((char*)td + HEAP_TUPLE_HEADER_SIZE), values, data_size);

    return htup;
}