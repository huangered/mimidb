#include "node/parsenode.hpp"
#include "util/mctx.hpp"

Node*
makeExpr(char* param) {
	ExprStmt* node = (ExprStmt*)palloc(sizeof(ExprStmt));
	node->nodetag = NT_ExprStmt;
	node->key = param;
	return (Node*)node;
}

Node*
makeIntValue(int i) {
	IntValue* v = (IntValue*)palloc(sizeof(IntValue));
	v->nodetag = NT_IntValue;
	v->number = i;
	return (Node*)v;
}

Node*
makeStrValue(char* str) {
	StrValue* v = (StrValue*)palloc(sizeof(StrValue));
	v->nodetag = NT_StrValue;
	v->str = str;
	return (Node*)v;
}
