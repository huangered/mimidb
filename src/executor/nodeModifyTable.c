#include "executor/nodeModifyTable.h"

#include "access/rel.h"

void ExecInsertTuple(Relation rel, struct TupleSlotDesc* slot);
void ExecInsertIndex(Relation rel, struct TupleSlotDesc* slot);

void
ExecInsert(Relation rel, struct TupleSlotDesc* slot) {

    // insert into heap.
    ExecInsertTuple(rel, slot);
    // insert into index.
    ExecInsertIndex(rel, slot);
}

void
ExecInsertTuple(Relation rel, struct TupleSlotDesc* slot) {
    // rel->tb_am->tuple_insert(rel, slot);
}

void
ExecInsertIndex(Relation rel, struct TupleSlotDesc* slot) {
    // find index rel
    // rel->index_am->aminsert(rel, slot->key, slot->tts_tid);
}
