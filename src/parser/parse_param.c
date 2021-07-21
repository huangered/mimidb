#include "node/parsenode.h"

Node*
makeParam(char* param1, char* param2) {
    ParamStmt* node = (ParamStmt*)malloc(sizeof(ParamStmt));
    node->nodetag = NT_ParamStmt;
    node->key = param1;
    node->type = param2;
    return (Node*)node;
}

Node*
makeCreateTableParam(char* col_name, char* type, int primary) {
    CreateTableParam* node = (CreateTableParam*)malloc(sizeof(CreateTableParam));
    node->nodetag = NT_CreateTableParam;
    node->colname = col_name;
    node->type = type;
    node->primary = primary;
    return (Node*)node;
}

Node*
makeTypeName(char* type_name) {
    TypeName* name = (TypeName*)malloc(sizeof(TypeName));
    name->name = type_name;
    return (Node*)name;
}

Node*
makeColumnDef(char* col_name, TypeName* type_name, int primary) {
    ColumnDef* def = (ColumnDef*)malloc(sizeof(ColumnDef));
    def->colname = col_name;
    def->typeName = type_name;
    return (Node*)def;
}
