#ifndef _ACCESS_HEAP_H_
#define _ACCESS_HEAP_H_

#include "mimi.h"
#include "rel.h"
#include "storage/bufmgr.h"
#include "access/heaptuple.h"


extern void heapbuildempty(Relation rel);
extern bool heap_tuple_insert(Relation rel, TupleSlotDesc* slot);
extern bool heapremove(Relation rel, int key);
extern bool heapgettuple(HeapScanDesc scan);
extern bool heapbeginscan(HeapScanDesc scan);
extern HeapTuple heapgetnext(HeapScanDesc scan);
extern bool heapendscan(HeapScanDesc scan);
extern void heap_vacuum(Relation rel);
// for catalog usage
extern void simple_heap_insert(Relation rel, HeapTuple tup);

// internal methods
HeapTuple _heap_buildtuple(Relation rel, TupleSlotDesc* slot);

Buffer GetBufferForTuple(Relation rel, Size len);
void RelationPutHeapTuple(Relation rel, Buffer buf, HeapTuple htup);

// for debug
void print_heap(Relation rel);


#endif // !_HEAP_H_
