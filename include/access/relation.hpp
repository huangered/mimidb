#ifndef _relation_h_
#define _relation_h_

#include "access/relcache.hpp"

Relation relation_open(Oid relid);
void relation_close(Relation rel);

#endif // !_relation_h_
