#include "node/parsenode.h"
#include "util/mctx.h"

Node* makeParam(char* param1, char* param2) {
	ParamStmt* node = palloc(sizeof(ParamStmt));
	node->nodetag = NT_ParamStmt;
	node->key = param1;
	node->type = param2;
	return (Node*)node;
}

Node*
makeCreateTableParam(char* col_name, char* type, bool primary) {
	CreateTableParam* node = palloc(sizeof(CreateTableParam));
	node->nodetag = NT_CreateTableParam;
	node->colname = col_name;
	node->type = type;
	node->primary = primary;
	return (Node*)node;
}