#ifndef _node_hpp_
#define _node_hpp_

#include <stdlib.h>

typedef enum NodeTag {
    // ddl
    NT_InsertStmt,
    NT_UpdateStmt,
    NT_SelectStmt,
    NT_DeleteStmt,
    // dml
    NT_CreateTableStmt,

    NT_WhereStmt,
    NT_ExprStmt,
    NT_ParamStmt,
    NT_CreateTableParam,

    NT_AssignStmt,
    // for expr right value
    NT_IntValue,
    NT_StrValue,

    // for list
    NT_List,
    NT_IntList,
} NodeTag;

typedef struct Node {
    NodeTag nodetag;
} Node;

typedef enum Op {
    OP_AND,
    OP_OR,
    OP_NOT,
} Op;

#endif
