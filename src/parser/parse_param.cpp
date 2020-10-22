#include "node/parsenode.hpp"
#include "util/mctx.hpp"

Node* makeParam(char* param1, char* param2) {
	ParamStmt* node = (ParamStmt*)palloc(sizeof(ParamStmt));
	node->nodetag = NT_ParamStmt;
	node->key = param1;
	node->type = param2;
	return (Node*)node;
}

Node*
makeCreateTableParam(char* col_name, char* type, bool primary) {
	CreateTableParam* node = (CreateTableParam*)palloc(sizeof(CreateTableParam));
	node->nodetag = NT_CreateTableParam;
	node->colname = col_name;
	node->type = type;
	node->primary = primary;
	return (Node*)node;
}

NodePtr
makeTypeName(char* type_name) {
	TypeName* name = (TypeName*)palloc(sizeof(TypeName));
	name->name = type_name;
	return (NodePtr)name;
}

NodePtr
makeColumnDef(char* col_name, TypeName* type_name, bool primary) {
	ColumnDef* def = (ColumnDef*)palloc(sizeof(ColumnDef));
	def->colname = col_name;
	def->typeName = type_name;
	return (NodePtr)def;
}
