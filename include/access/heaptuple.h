#ifndef _heaptuple_h_
#define _heaptuple_h_

typedef struct HeapTupleData {
    int len;
    int xmin;
    int xmax;
    int ctid;
    int tag;
    int key;
    int value;
} HeapTupleData;

typedef HeapTupleData* HeapTuple;

#endif // !_heaptuple_h_
