#ifndef _access_heap_hpp_
#define _access_heap_hpp_

#include "mimi.hpp"
#include "access/relation.hpp"
#include "access/heaptuple.hpp"
#include "access/scankey.hpp"
#include "access/tbapi.hpp"
/*
堆表操作类
*/
class Heap {
public:
	Relation Open(Oid relationId);
	void Close(Relation rel);

	bool Insert(Relation rel, HeapTuple tuple);
	void Update(Relation rel, HeapTuple tuple);
	bool Remove(Relation rel, int key);

	// search
	HeapScanDesc BeginScan(Relation rel, int nkeys, ScanKey key);
	HeapTuple GetNext(HeapScanDesc scan);
	bool EndScan(HeapScanDesc scan);

	void Vacuum(Relation rel);
	// for catalog usage
	void simple_heap_insert(Relation rel, HeapTuple tup);
private:
	// internal methods
	HeapTuple _heap_buildtuple(Relation rel, TupleSlotDesc* slot);
	HeapTuple _tuple_prepare_insert(Relation rel, HeapTuple tup, int xmin);


	Buffer GetBufferForTuple(Relation rel, Size len);
	void RelationPutHeapTuple(Relation rel, Buffer buf, HeapTuple htup);
	bool heapgettuple(HeapScanDesc scan);
};

Heap* route();

#endif // !_access_heap_hpp_
