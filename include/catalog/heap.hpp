#ifndef _heap_catalog_h_
#define _heap_catalog_h_

#include "mimi.hpp"
#include "access/relcache.hpp"
#include "access/tupledesc.hpp"

Relation heap_create_with_catalog(const char* relname, Oid relid, TupleDesc tupDesc);

#endif