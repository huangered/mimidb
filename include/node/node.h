#ifndef _NODE_H_
#define _NODE_H_

#include "mimi.h"

typedef enum NodeTag {
	NT_InsertStmt,
	NT_UpdateStmt,
	NT_SelectStmt,
	NT_CreateTableStmt,

	NT_WhereStmt,
	NT_ExprStmt,
	NT_ParamStmt,

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


#endif
