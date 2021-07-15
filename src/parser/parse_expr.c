#include "node/parsenode.h"

Node*
makeExpr(char* param) {
    ExprStmt* node = (ExprStmt*)malloc(sizeof(ExprStmt));
    node->nodetag = NT_ExprStmt;
    node->key = param;
    return (Node*)node;
}

Node*
makeIntValue(int i) {
    IntValue* v = (IntValue*)malloc(sizeof(IntValue));
    v->nodetag = NT_IntValue;
    v->number = i;
    return (Node*)v;
}

Node*
makeStrValue(char* str) {
    StrValue* v = (StrValue*)malloc(sizeof(StrValue));
    v->nodetag = NT_StrValue;
    v->str = str;
    return (Node*)v;
}
