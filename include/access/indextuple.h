#ifndef _index_tuple_h_
#define _index_tuple_h_

typedef struct IndexTupleData {
    int t_tid;
    int t_info;
    int key;
    int value;
} IndexTupleData;

typedef IndexTupleData* IndexTuple;

#endif // !_index_tuple_h_
