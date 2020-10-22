#ifndef _index_catalog_h_
#define _index_catalog_h_

#include "mimi.hpp"
#include "access/tupledesc.hpp"
#include "access/relcache.hpp"

Relation index_create(const char* name, Oid heaprelid, Oid indexrelid, TupleDesc tupdesc);

#endif