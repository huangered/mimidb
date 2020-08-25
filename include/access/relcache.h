#ifndef _rel_cache_h_
#define _rel_cache_h_

#include "access/tupledesc.h"
#include "mimi.h"

typedef struct RelationData* Relation;


extern Relation RelationIdGetRelation(Oid relid);
extern void RelationClose(Relation rel);
extern Relation BuildRelation(Oid oid, const char* name, TupleDesc tupdesc);

#endif // !_rel_cache_h_
