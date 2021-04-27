#include "access/heaptuple.hpp"
#include "access/tupledesc.hpp"
#include "util/mctx.hpp"

HeapTuple
heap_form_tuple(TupleDesc desc, Datum* values) {
    int datasz{};
    HeapTupleHeader td{};

    for (int i{}; i < desc->natts; i++) {
        datasz += desc->attr[i].att_len;
    }

    int hoff = HEAP_TUPLE_HEADER_SIZE;
    int len = HEAP_TUPLE_SIZE + hoff + datasz;
    HeapTuple htup = (HeapTuple)palloc0(len);

    htup->t_len = datasz + hoff;
    htup->t_data = td = (HeapTupleHeader)((char*)htup + HEAP_TUPLE_SIZE);

    // for simple, we only have (key,value) now.
    memcpy(((char*)td + hoff), values, datasz);
    return htup;
}

/*
* 复制一个新的heap tuple对象
*/
HeapTuple
heap_copytuple(HeapTuple htup) {
    return htup;
}

// 释放heaptuple
void
heap_free_tuple(HeapTuple tuple) {
    
    pfree(tuple);
}
