#ifndef _heapio_hpp_
#define _heapio_hpp_

#include "access/heaptuple.hpp"
#include "storage/buf.hpp"
#include "access/rel.hpp"

void RelationPutHeapTuple(Relation rel, Buffer buffer);
Buffer RelationGetBufferForTuple(Relation rel, Size len);

#endif
