#include "state.h"

#include <stdlib.h>
#include <string.h>

State*
state_new(int nitems, ItemNumber* core) {
    int items_size     = nitems * sizeof(ItemNumber*);
    State* state       = malloc(items_size + offsetof(State, items));
    state->number      = nstates++;
    state->transitions = NULL;
    state->reductions  = NULL;
    state->nitems      = nitems;
    memcpy(state->items, core, items_size);

    // todo: 插入state hash

    return state;
}

void
state_free(State* state) {
    free(state->transitions);
    free(state->reductions);
    free(state);
}