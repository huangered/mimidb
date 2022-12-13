#ifndef _heaptuple_h_
#define _heaptuple_h_

#include "mimi.h"
#include "access/tupledesc.h"
#include "storage/itemptr.h"

struct HeapTupleFields {
    int t_xmin;
    int t_xmax;
};

struct HeapTupleHeaderData {
    struct HeapTupleFields t_heap;
    struct ItemPointerData t_ctid;
};

typedef struct HeapTupleHeaderData* HeapTupleHeader;

struct HeapTupleData {
    int t_len;              /* 数据 values 的长度 */
    HeapTupleHeader t_data; // 数据头和数据指针
};

typedef struct HeapTupleData* HeapTuple;

#define HEAP_TUPLE_SIZE        sizeof(struct HeapTupleData)
#define HEAP_TUPLE_HEADER_SIZE sizeof(struct HeapTupleHeaderData)

HeapTuple heap_form_tuple(TupleDesc desc, Datum* values);
void heap_free_tuple(HeapTuple tuple);

#endif // !_heaptuple_h_
