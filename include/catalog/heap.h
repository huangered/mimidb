#ifndef _heap_catalog_hpp_
#define _heap_catalog_hpp_

#include "mimi.h"
#include "access/relcache.h"
#include "access/tupledesc.h"

Relation heap_create_with_catalog(const char* relname, Oid relid, TupleDesc tupDesc);

#endif