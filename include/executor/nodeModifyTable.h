#ifndef _node_modify_table_h_
#define _node_modify_table_h_

#include "mimi.h"
#include "access/relcache.h"
#include "executor/tuptable.h"

extern void ExecModifyTable(Relation rel);
extern void ExecInsert(Relation rel, struct TupleSlotDesc* slot);

#endif // !_node_modify_table_h_
