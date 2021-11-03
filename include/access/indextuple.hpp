#ifndef _index_tuple_h_
#define _index_tuple_h_

#include "access/tupledesc.hpp"
#include "storage/itemptr.hpp"

typedef struct IndexTupleData {
    ItemPointerData t_tid;
    int t_info;
    int key;      // will remove when heap is ready.
    int value;    // will remove when heap is ready.
} IndexTupleData; // values 数据是放置在它后面

typedef IndexTupleData* IndexTuple;

extern IndexTuple index_form_tuple(TupleDesc tupdesc, Datum* values);

#endif // !_index_tuple_h_
