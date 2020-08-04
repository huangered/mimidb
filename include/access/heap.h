#ifndef _HEAP_H_
#define _HEAP_H_

#include "mimi.h"
#include "rel.h"



extern void heapbuildempty(Relation rel);
extern bool heapinsert(Relation rel, int key, int value);
extern bool heapremove(Relation rel, int key);
extern bool heapgettuple(Relation rel, int key, int* value);

#endif // !_HEAP_H_
