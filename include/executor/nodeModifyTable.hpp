#ifndef _node_modify_table_h_
#define _node_modify_table_h_

#include "mimi.hpp"
#include "access/relcache.hpp"
#include "executor/tuptable.hpp"

void ExecModifyTable(Relation rel);
void ExecInsert(Relation rel, TupleSlotDesc* slot);

#endif // !_node_modify_table_h_
