#ifndef _storage_h_
#define _storage_h_

#include "access/relcache.h"

extern void RelationCreateStorage(Relation rel);
extern void RelationDropStorage(Relation rel);

#endif