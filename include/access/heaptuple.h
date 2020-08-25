#ifndef _heaptuple_h_
#define _heaptuple_h_

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

#endif // !_heaptuple_h_
