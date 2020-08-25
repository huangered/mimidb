#ifndef _heap_h_
#define _heap_h_

#include "mimi.h"
#include "access/relcache.h"
#include "access/tupledesc.h"

Relation heap_create(const char* relname, Oid relid, TupleDesc tupDesc);

#endif