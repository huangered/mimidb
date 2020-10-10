#ifndef _PARSENODE_H_
#define _PARSENODE_H_

#include "node/node.h"
#include "util/list.h"


typedef struct NodeWrap {
	Node* node;
} NodeWrap;

typedef struct ExprStmt {
	NodeTag nodetag;
	char* key;
} ExprStmt;

typedef struct SelectStmt {
	NodeTag nodetag;
	char* relname;
	List* columns;
} SelectStmt;

typedef struct InsertStmt {
	NodeTag nodetag;
	char* relname;
	List* columns;
} InsertStmt;


typedef struct CreateTableStmt {
	NodeTag nodetag;
	char* relname;
	List* columns;
} CreateTableStmt;

typedef struct ParamStmt {
	NodeTag nodetag;
	char* key;
	char* type;
} ParamStmt;

Node* makeExpr(char* key);
Node* makeParam(char* param1, char* param2);
Node* makeSelectStmt(char* tbl_name, List* cols);
Node* makeInsertStmt(char* tbl_name, List* cols);
Node* makeUpdateStmt(char* tbl_name);
Node* makeCreateTableStmt(char* tbl_name, List* cols);

#endif