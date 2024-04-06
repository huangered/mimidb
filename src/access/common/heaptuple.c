#include "access/heaptuple.h"
#include "access/tupledesc.h"

HeapTuple
heap_form_tuple(TupleDesc desc, Datum* values) {

    HeapTuple tuple;    // 返回值
    HeapTupleHeader td; // data
    Size len, datalen;
    int hoff;
    int datasz;

    for (int i = 0; i < desc->natts; i++) {
        datasz += desc->attr[i].att_len;
    }

    // 决定要多大的空间
    len = offsetof(HeapTupleHeaderData, t_bits);

    hoff = len = MAXALIGN(len);

    datalen = heap_compute_data_size(desc, values);

    len += datalen;

    HeapTuple htup = (HeapTuple)palloc0(HEAP_TUPLE_SIZE + len);
    htup->t_data = td = (HeapTupleHeader)((char*)htup + HEAP_TUPLE_SIZE);

    htup->t_len = len;

    heap_fill_tuple(desc, values, (char*)td + hoff, datalen);
    return htup;
}

// 释放heaptuple
void
heap_free_tuple(HeapTuple tuple) {

    pfree(tuple);
}
