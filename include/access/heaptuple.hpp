#ifndef _heaptuple_h_
#define _heaptuple_h_

#include "mimi.hpp"
#include "access/tupledesc.hpp"

typedef struct HeapTupleFields {
    int t_xmin;
    int t_xmax;
} HeapTupleFields;

typedef struct ItemPointerData {
    int blocknum;
    int offset;
} ItemPointerData;

typedef ItemPointerData* ItemPointer;

typedef struct HeapTupleHeaderData {
    HeapTupleFields t_heap;

    ItemPointerData t_ctid;
    int t_hoff;
} HeapTupleHeaderData;

typedef HeapTupleHeaderData* HeapTupleHeader;

typedef struct HeapTupleData {
    int t_len;  /* length of t_data */
    Oid t_tableOid;
    HeapTupleHeader t_data; // tuple header and data
} HeapTupleData;

typedef HeapTupleData* HeapTuple;

#define HEAP_TUPLE_SIZE     sizeof(HeapTupleData)

extern HeapTuple heap_form_tuple(TupleDesc desc, Datum* values);

#endif // !_heaptuple_h_
