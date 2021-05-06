#include "executor/nodeModifyTable.hpp"

#include "util/mctx.hpp"
#include "access/rel.hpp"


void ExecInsertTuple(Relation rel, TupleSlotDesc* slot);
void ExecInsertIndex(Relation rel, TupleSlotDesc* slot);

/*
插入记录
*/
void
ExecInsert(Relation rel, TupleSlotDesc *slot) {

    // insert into heap.
    ExecInsertTuple(rel, slot);
    // insert into index.
    ExecInsertIndex(rel, slot);
}

void
ExecInsertTuple(Relation rel, TupleSlotDesc* slot) {
    //rel->tb_am->tuple_insert(rel, slot);
}

void
ExecInsertIndex(Relation rel, TupleSlotDesc* slot) {
    // find index rel
    //rel->index_am->aminsert(rel, slot->key, slot->tts_tid);
}
