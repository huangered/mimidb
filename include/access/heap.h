#ifndef _HEAP_H_
#define _HEAP_H_

#include "mimi.h"
#include "rel.h"

extern void heapbuildempty(Relation rel);
extern bool heapinsert(Relation rel);
extern bool heapremove(Relation rel);
extern bool heapgettuple(Relation rel);

#endif // !_HEAP_H_
