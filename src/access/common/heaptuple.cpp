#include "access/heaptuple.hpp"
#include "access/tupledesc.hpp"
#include "util/mctx.hpp"

HeapTuple
heap_form_tuple(TupleDesc desc, Datum* values) {
    int datasz{};
    HeapTupleHeader td{};

    for (int i{}; i < desc->GetNatts(); i++) {
        datasz += desc->GetNatt(i)->att_len;
    }

    int hoff = HEAP_TUPLE_HEADER_SIZE;
    int len = HEAP_TUPLE_SIZE + hoff + datasz;
    HeapTuple htup = (HeapTuple)std::malloc(len);

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
    
    std::free(tuple);
}

HeapTupleData2::HeapTupleData2(TupleDesc tupdesc, Datum* values) {
    int datasz{};
    HeapTupleHeader td{};

    for (int i{}; i < tupdesc->GetNatts(); i++) {
        datasz += tupdesc->GetNatt(i)->att_len;
    }

    t_len = HEAP_TUPLE_HEADER_SIZE + datasz;
    HeapTupleHeader header = (HeapTupleHeader)new char[t_len];

    // for simple, we only have (key,value) now.
    memcpy(((char*)header + HEAP_TUPLE_HEADER_SIZE), values, datasz);
    t_data = header;
}

HeapTupleData2::~HeapTupleData2() {
    delete[] (char*)t_data;
}

HeapTuple2
HeapTupleData2::CopyTuple() {
    return nullptr;
}

char*
HeapTupleData2::GetStruct() {
    return (char*)t_data + HEAP_TUPLE_HEADER_SIZE;
}