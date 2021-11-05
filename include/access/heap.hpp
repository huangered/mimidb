#ifndef _access_heap_hpp_
#define _access_heap_hpp_

#include "mimi.hpp"
#include "access/relation.hpp"
#include "access/heaptuple.hpp"
#include "access/scankey.hpp"
#include "access/scan.hpp"
#include "access/tableapi.hpp"

/* in heap.cpp*/
extern Relation relation_open(Oid relationId);
extern void relation_close(Relation relation);

extern Relation heap_open(Oid relationId);
extern void heap_close(Relation relation);

/* heap api */
extern HeapScanDesc heap_beginscan(Relation rel, int nkeys, ScanKey key);
extern void heap_endscan(HeapScanDesc scan);
extern HeapTuple heap_getnext(HeapScanDesc scan, ScanDirection direction);
extern Oid heap_insert(Relation relation, HeapTuple tup);
extern void heap_delete(Relation relation, ItemPointer tid);
extern void heap_sync(Relation relation);

extern void simple_heap_insert(Relation relation, HeapTuple tup);

#endif // !_access_heap_hpp_
