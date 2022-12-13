#ifndef _relcache_hpp_
#define _relcache_hpp_

#include "mimi.h"
#include "access/heaptuple.h"
#include "access/relation.h"
#include "access/tupledesc.h"
#include "util/hashmap.h"

extern void RelationCacheInitialize(void);

struct RelCacheEntry {
    Oid oid;
    Relation rel;
};

extern Relation RelationIdGetRelation(Oid relid);
extern void RelationClose(Relation rel);
extern Relation BuildLocalRelation(Oid oid, const char* name, TupleDesc tupDesc);
extern Relation BuildRelationDesc(Oid oid, bool insert);

extern void _formrdesc(const char* relname, Oid reltype, int natts, const struct FormData_mimi_attribute* attrs);
extern void _relationBuildTuple(Relation rel, TupleDesc tupleDesc);
extern HeapTuple _scanMimiRelation(Oid relid);

#endif // !_rel_cache_h_
