#ifndef _node_hpp_
#define _node_hpp_

enum NodeTag
{
    // ddl
    NT_InsertStmt = 0,
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
};

typedef enum NodeTag NodeTag;

class Node {
public:
    NodeTag nodetag;
};

typedef enum Op
{
    OP_AND,
    OP_OR,
    OP_NOT,
} Op;

#endif
