#ifndef _gram_h_
#define _gram_h_

#include "global.h"
#include "symtab.h"

#define ISTOKEN(i) ((i) < Params.ntokens)
#define ISVAR(i)   ((i) >= Params.ntokens)

typedef int RuleNumber;
typedef int ItemNumber;

/*--------.
| Rules.  |
`--------*/
typedef struct rule {
    RuleNumber user_number; // rule的id号
    Symbol* lhs;
    ItemNumber* rhs;
} Rule;

static Rule* rules;

static Symbol** symbols;

#endif // ! _gram_h_
