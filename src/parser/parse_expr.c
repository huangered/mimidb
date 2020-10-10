#include "node/parsenode.h"
#include "util/mctx.h"

Node* makeExpr(char* param) {
	ExprStmt* node = palloc(sizeof(ExprStmt));
	node->nodetag = NT_ExprStmt;
	node->key = param;
	return node;
}

Node*
makeIntValue(int i) {
	IntValue* v = palloc(sizeof(IntValue));
	v->nodetag = NT_IntValue;
	v->number = i;
	return v;
}

Node*
makeStrValue(char* str) {
	StrValue* v = palloc(sizeof(StrValue));
	v->nodetag = NT_StrValue;
	v->str = str;
	return v;
}
