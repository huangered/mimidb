#ifndef _relcache_hpp_
#define _relcache_hpp_

#include "mimi.hpp"
#include "access/heaptuple.hpp"
#include "access/relation.hpp"
#include "access/tupledesc.hpp"
#include "util/hashmap.hpp"

struct RelCacheEntry {
	Oid oid;
	Relation rel;
};

class RelCache {
private:
	HashMap<Oid, RelCacheEntry> cache;
public:
	RelCache();
	Relation RelationIdGetRelation(Oid relid);
	void RelationClose(Relation rel);
	Relation BuildLocalRelation(Oid oid, const char* name, TupleDesc tupDesc);
	Relation BuildRelationDesc(Oid oid, bool insert);
private:
	void _formrdesc(const char* relname, Oid reltype, int natts, const FormData_mimi_attribute* attrs);
	void _relationBuildTuple(Relation rel, TupleDesc tupleDesc);
	HeapTuple _scanMimiRelation(Oid relid);
};

extern RelCache* relcache;

#endif // !_rel_cache_h_
