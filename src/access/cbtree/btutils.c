#include "access/btree.h"
#include "util/mctx.h"

void _bt_freestack(BTStack stack) {
    while (stack != NULL) {
        BTStack parent = stack->parent;
        pfree(stack);
        stack = parent;
    }
}