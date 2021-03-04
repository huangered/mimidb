#ifndef _ACCESS_HEAP_H_
#define _ACCESS_HEAP_H_

#include "mimi.hpp"
#include "rel.hpp"
#include "storage/bufmgr.hpp"
#include "access/heaptuple.hpp"
#include "access/scankey.hpp"

class HeapIndex {
private:
	std::shared_ptr<BufferMgr> _bufMgr;
public:
	void heapbuildempty(Relation rel);
	bool heap_tuple_insert(Relation rel, TupleSlotDesc* slot);
	bool heapremove(Relation rel, int key);
	bool heapgettuple(HeapScanDesc scan);
	HeapScanDesc heapbeginscan(Relation rel, int nkeys, ScanKey key);
	HeapTuple heapgetnext(HeapScanDesc scan);
	bool heapendscan(HeapScanDesc scan);
	void heap_vacuum(Relation rel);
	// for catalog usage
	void simple_heap_insert(Relation rel, HeapTuple tup);

	// internal methods
	HeapTuple _heap_buildtuple(Relation rel, TupleSlotDesc* slot);

	Buffer GetBufferForTuple(Relation rel, Size len);
	void RelationPutHeapTuple(Relation rel, Buffer buf, HeapTuple htup);

	// for debug
	void print_heap(Relation rel);
private:
	bool heap_insert(Relation rel, HeapTuple tup);
	HeapTuple heaptuple_prepare_insert(Relation rel, HeapTuple tup, int xmin);
};

#endif // !_HEAP_H_
