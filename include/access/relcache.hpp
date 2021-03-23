 #ifndef _rel_cache_h_
#define _rel_cache_h_

#include "access/tupledesc.hpp"
#include "mimi.hpp"
#include "util/hashmap.hpp"
#include "access/heaptuple.hpp"

typedef struct RelationData* Relation;

void RelationCacheInit();

Relation RelationIdGetRelation(Oid relid);
void RelationClose(Relation rel);
Relation BuildLocalRelation(Oid oid, const char* name, TupleDesc tupDesc);
Relation BuildRelationDesc(Oid oid, bool insert);

struct RelCacheEntry {
	Oid oid;
	Relation rel;
};

class RelCache {
private:
	HashMap<Oid, RelCacheEntry> _relhash;
public:
	RelCache();
public:
	Relation GetRelation(Oid id);
	void CloseRelation(Relation rel);
	Relation BuildLocalRelation(Oid oid, const char* name, TupleDesc tupDesc);
	Relation BuildRelationDesc(Oid oid, bool insert);
private:

	void _formrdesc(const char* relname, Oid reltype, int natts, const FormData_mimi_attribute* attrs);
	void _relationBuildTuple(Relation rel, TupleDesc tupleDesc);
	HeapTuple _scanMimiRelation(Oid relid);
};
#endif // !_rel_cache_h_
