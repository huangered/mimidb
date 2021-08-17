#ifndef _state_h_
#define _state_h_

#include "bitset.h"
#include "gram.h"

typedef int StateNumber;

typedef struct state State;

// transitions 转移
typedef struct transition {
    int num;
    State* states[1];
} Transition;

Transition* transition_new(int num);

// reduction 归约
typedef struct reduction {
    int num;
    Bitset* lookaheadTokens;
} Reduction;

Reduction* reduction_new(int num);

// state
typedef struct state {
    StateNumber number;
    Transition* transitions;
    Reduction* reductions;

    int nitems;
    ItemNumber items[1];
} State;

static StateNumber nstates;

State* state_new(int nitems, ItemNumber* core);
void state_free(State* state);

typedef struct statelist {
    State* state;
    struct statelist* next;
} StateList;

#endif