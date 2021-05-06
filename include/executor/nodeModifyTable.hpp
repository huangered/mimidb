#ifndef _node_modify_table_h_
#define _node_modify_table_h_

#include "access/relcache.hpp"
#include "executor/tuptable.hpp"
#include "node/parsenode.h"

void ExecModifyTable(Relation rel);
void ExecInsert(Relation rel, TupleSlotDesc* slot);
void ExecSelect(Relation rel, SelectStmt* stmt);

#endif // !_node_modify_table_h_
