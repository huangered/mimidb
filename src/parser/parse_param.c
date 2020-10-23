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

Node*
makeTypeName(char* type_name) {
	TypeName* name = palloc(sizeof(TypeName));
	name->name = type_name;
	return (Node*)name;
}

Node*
makeColumnDef(char* col_name, TypeName* type_name, bool primary) {
	ColumnDef* def = palloc(sizeof(ColumnDef));
	def->colname = col_name;
	def->typeName = type_name;
	def->primary = primary;
	return (Node*)def;
}
