#ifndef _node_modify_table_h_
#define _node_modify_table_h_

#include "mimi.h"
#include "access/relcache.h"
#include "executor/tuptable.h"

void ExecModifyTable(Relation rel);
void ExecInsert(Relation rel, TupleSlotDesc* slot);

#endif // !_node_modify_table_h_
