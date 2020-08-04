#ifndef _index_tuple_h_
#define _index_tuple_h_

typedef struct IndexTupleData {
    int t_tid;
    int t_info;
    int key;    // will remove when heap is ready.
    int value;  // will remove when heap is ready.
} IndexTupleData;

typedef IndexTupleData* IndexTuple;

#endif // !_index_tuple_h_
