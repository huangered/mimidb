#ifndef _heaptuple_h_
#define _heaptuple_h_

#include "mimi.h"
#include "access/tupledesc.h"
#include "storage/itemptr.h"

typedef struct HeapTupleFields {
    int t_xmin;
    int t_xmax;
} HeapTupleFields;

struct HeapTupleHeaderData {
    union {
        struct HeapTupleFields t_heap;
    } t_choice;
    ItemPointerData t_ctid; // current TID

    /* 目前是杂项 */
    uint16 t_infomask2;
    uint16 t_infomask;
    uint8 t_hoff;
    bits8 t_bits[0];
    // 数据
};

typedef struct HeapTupleHeaderData HeapTupleHeaderData;

#define SizeofHeapTupleHeader offsetof(HeapTupleHeaderData, t_bits)

typedef struct HeapTupleHeaderData* HeapTupleHeader;

typedef struct HeapTupleData {
    int t_len;              /* 数据 values 的长度 */
    HeapTupleHeader t_data; // 数据头和数据指针
} HeapTupleData;

typedef HeapTupleData* HeapTuple;

#define HEAP_TUPLE_SIZE        sizeof(struct HeapTupleData)
#define HEAP_TUPLE_HEADER_SIZE sizeof(struct HeapTupleHeaderData)

extern void heap_fill_tuple(TupleDesc tupleDesc, Datum* values, char* data, Size data_size);
extern HeapTuple heap_form_tuple(TupleDesc desc, Datum* values);
extern void heap_free_tuple(HeapTuple tuple);

#endif // !_heaptuple_h_
