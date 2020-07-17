#ifndef _CB_TREE_H_
#define _CB_TREE_H_

#include "mimi.h"
#include "rel.h"

extern void btbuildempty(Relation rel);
extern bool btinsert(Relation rel);
extern bool btremove(Relation rel);
extern bool btgettuple(Relation rel);

#endif