#ifndef _heap_h_
#define _heap_h_

#include "mimi.h"
#include "access/relcache.h"

Relation heap_create(const char* relname, Oid relid);

#endif