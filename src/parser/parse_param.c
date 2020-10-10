#include "node/parsenode.h"
#include "util/mctx.h"

Node* makeParam(char* param1, char* param2) {
	ParamStmt* node = palloc(sizeof(ParamStmt));
	node->nodetag = NT_ParamStmt;
	node->key = param1;
	node->type = param2;
	return node;
}