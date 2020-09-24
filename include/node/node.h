#ifndef _NODE_H_
#define _NODE_H_

#include "mimi.h"

typedef enum NodeTag {
	NT_SelectStmt,
	NT_CreateStmt,
} NodeTag;

typedef struct Node {
	NodeTag nodetag;
} Node;

typedef struct NodeWrap {
	Node* node;
} NodeWrap;

typedef struct SelectStmt {
	NodeTag nodetag;
	char* relname;
	char* column;
} SelectStmt;

typedef struct CreateStmt {
	NodeTag nodetag;
	char* relname;
	char* column;
} CreateStmt;

Node* makeSelectStmt(char* a1, char* a2);

#endif
