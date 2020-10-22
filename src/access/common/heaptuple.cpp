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

    int hoff = sizeof(HeapTupleHeaderData);
    int len = HEAP_TUPLE_SIZE + hoff + data_size;

    htup = (HeapTuple)palloc(len);
    htup->t_len = data_size + hoff;
    htup->t_data = td = (HeapTupleHeader)((char*)htup + HEAP_TUPLE_SIZE);
    htup->t_data->t_hoff = hoff;

    memcpy(((char*)td + hoff), values, data_size);

    return htup;
}