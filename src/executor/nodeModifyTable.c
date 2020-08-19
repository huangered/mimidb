#include "executor/nodeModifyTable.h"

typedef struct TupleSlotDesc {
    int ctid;
    int key;
    int value;
};

void ExecInsert(Oid oid, int key, int value) {
    // insert into heap.

    // insert into index.
}