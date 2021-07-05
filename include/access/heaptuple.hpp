#ifndef _heaptuple_h_
#define _heaptuple_h_

#include "mimi.hpp"
#include "access/tupledesc.hpp"
#include "storage/itemptr.hpp"

struct HeapTupleFields {
    int t_xmin;
    int t_xmax;
};

struct HeapTupleHeaderData {
    HeapTupleFields t_heap;
    ItemPointerData t_ctid;
};

typedef HeapTupleHeaderData* HeapTupleHeader;

struct HeapTupleData {
    int t_len;              /* 数据 values 的长度 */
    HeapTupleHeader t_data; // 数据头和数据指针
};

typedef HeapTupleData* HeapTuple;

#define HEAP_TUPLE_SIZE            sizeof(HeapTupleData)
#define HEAP_TUPLE_HEADER_SIZE     sizeof(HeapTupleHeaderData)

#define GETSTRUCT(tup) ((char*)((tup)->t_data) + HEAP_TUPLE_HEADER_SIZE)

HeapTuple heap_form_tuple(TupleDesc desc, Datum* values);
void heap_free_tuple(HeapTuple tuple);
HeapTuple heap_copytuple(HeapTuple htup);

typedef class HeapTupleData2* HeapTuple2;

class HeapTupleData2 {
    int t_len;
    HeapTupleHeader t_data;
public:
    HeapTupleData2(TupleDesc tupdesc, Datum* values);
    ~HeapTupleData2();

    HeapTuple2 CopyTuple();
    char* GetStruct();
};

#endif // !_heaptuple_h_
