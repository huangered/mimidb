#ifndef _access_heap_hpp_
#define _access_heap_hpp_

#include "mimi.hpp"
#include "access/relation.hpp"
#include "access/heaptuple.hpp"
#include "access/scankey.hpp"
#include "access/scan.hpp"
#include "access/tableapi.hpp"

typedef HeapScanDescData* HeapScanDesc;

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

	void debug(Relation rel);
private:
	// internal methods
	HeapTuple _tuple_prepare_insert(Relation rel, HeapTuple tup, int xmin);

	Buffer GetBufferForTuple(Relation rel, Size len);
	void RelationPutHeapTuple(Relation rel, Buffer buf, HeapTuple htup);
	void _heapGetTuple(HeapScanDesc scan);
};

Heap* HeapRoute();

#endif // !_access_heap_hpp_
