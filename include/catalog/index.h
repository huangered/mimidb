#ifndef _index_catalog_h_
#define _index_catalog_h_

#include "mimi.h"
#include "access/tupledesc.h"
#include "access/relcache.h"

Relation index_create(const char* name, Oid heaprelid, Oid indexrelid, TupleDesc tupdesc);

#endif