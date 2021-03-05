 #ifndef _rel_cache_h_
#define _rel_cache_h_

#include "access/tupledesc.hpp"
#include "mimi.hpp"

typedef struct RelationData* Relation;

extern void RelationCacheInit();

extern Relation RelationIdGetRelation(Oid relid);
extern void RelationClose(Relation rel);
extern Relation BuildLocalRelation(Oid oid, const char* name, TupleDesc tupDesc);
extern Relation BuildRelationDesc(Oid oid, bool insert);

class relcache {
public:
	Relation GetRelation(Oid id);
	void CloseRelation(Relation rel);
	Relation BuildLocalRelation(Oid oid, const char* name, TupleDesc tupDesc);
	Relation BuildRelationDesc(Oid oid, bool insert);
};
#endif // !_rel_cache_h_
