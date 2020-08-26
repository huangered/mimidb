#ifndef _rel_cache_h_
#define _rel_cache_h_

#include "access/tupledesc.h"
#include "mimi.h"

typedef struct RelationData* Relation;

extern void RelationCacheInit();

extern Relation RelationIdGetRelation(Oid relid);
extern void RelationClose(Relation rel);
extern Relation BuildLocalRelation(Oid oid, const char* name, TupleDesc tupDesc);
extern Relation BuildRelationDesc(Oid oid, bool insert);

#endif // !_rel_cache_h_
