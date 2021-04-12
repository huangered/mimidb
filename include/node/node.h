#ifndef _NODE_H_
#define _NODE_H_

#include <stdlib.h>

typedef enum NodeTag {
	NT_InsertStmt,
	NT_UpdateStmt,
	NT_SelectStmt,
	NT_DeleteStmt,
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

typedef struct Node* NodePtr;

#endif
