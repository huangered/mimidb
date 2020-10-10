#ifndef _NODE_H_
#define _NODE_H_

#include "mimi.h"

typedef enum NodeTag {
	NT_InsertStmt,
	NT_SelectStmt,
	NT_CreateTableStmt,

	NT_ExprStmt,
	NT_ParamStmt,

	// for list
	NT_List,
	NT_IntList,
} NodeTag;

typedef struct Node {
	NodeTag nodetag;
} Node;


#endif
