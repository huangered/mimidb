#ifndef _PARSENODE_H_
#define _PARSENODE_H_

#include "node/node.h"
#include "util/list.h"


typedef struct NodeWrap {
	Node* node;
} NodeWrap;

typedef struct SelectStmt {
	NodeTag nodetag;
	char* relname;
	List* column;
} SelectStmt;

typedef struct InsertStmt {
	NodeTag nodetag;
	char* relname;
	List* column;
} InsertStmt;


typedef struct CreateStmt {
	NodeTag nodetag;
	char* relname;
	List* column;
} CreateStmt;


Node* makeSelectStmt(char* tbl_name, List* a2);
Node* makeInsertStmt(char* tbl_name, List* a2);

#endif