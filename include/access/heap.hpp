#ifndef _access_heap_hpp_
#define _access_heap_hpp_

#include "mimi.hpp"
#include "access/relation.hpp"
#include "access/heaptuple.hpp"
#include "access/scankey.hpp"
#include "access/scan.hpp"
#include "access/tableapi.hpp"


/* */
extern Relation relation_open(Oid relationId);
extern void relation_close(Relation relation);

extern Relation heap_open(Oid relationId);
extern void heap_close(Relation relation);

/* heap api */

extern Oid heap_insert(Relation relation, HeapTuple tup);

/*
堆表操作类
*/
class Heap {
public:
    Heap();
    Relation Open(Oid relationId);
    void Close(Relation rel);

    bool Insert(Relation rel, HeapTuple tuple);
    void Update(Relation rel, HeapTuple tuple);
    bool Remove(Relation rel, int key);

    // search
    HeapScanDesc BeginScan(Relation rel, int nkeys, ScanKey key);
    HeapTuple GetNext(HeapScanDesc scan, ScanDirection direction);
    bool EndScan(HeapScanDesc scan);

    void Vacuum(Relation rel);
    // for catalog usage
    void simple_heap_insert(Relation rel, HeapTuple tup);

    void debug(Relation rel);

private:
    // internal methods
    HeapTuple _tuple_prepare_insert(Relation rel, HeapTuple tup, int xmin);

    Buffer _get_buffer_for_tuple(Relation rel, Size len);
    void _relation_put_heap_tuple(Relation rel, Buffer buf, HeapTuple htup);
    void _heap_get_tuple(HeapScanDesc scan, ScanDirection direction);
};

extern Heap* HeapRoute();

#endif // !_access_heap_hpp_
