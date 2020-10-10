#include "node/parsenode.h"
#include "util/mctx.h"

Node* makeExpr(char* param) {
	ExprStmt* node = palloc(sizeof(ExprStmt));
	node->nodetag = NT_ExprStmt;
	node->key = param;
	return node;
}