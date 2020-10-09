#ifndef _NODE_H_
#define _NODE_H_

#include "mimi.h"

typedef enum NodeTag {
	NT_InsertStmt,
	NT_SelectStmt,
	NT_CreateStmt,
} NodeTag;

typedef struct Node {
	NodeTag nodetag;
} Node;


#endif
