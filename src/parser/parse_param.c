#include "node/parsenode.h"

Node*
makeParam(char* param1, char* param2) {
    ParamStmt* node = new ParamStmt();
    node->nodetag   = NT_ParamStmt;
    node->key       = param1;
    node->type      = param2;
    return node;
}

Node*
makeCreateTableParam(char* col_name, char* type, int primary) {
    CreateTableParam* node = new CreateTableParam();
    node->nodetag          = NT_CreateTableParam;
    node->colname          = col_name;
    node->type             = type;
    node->primary          = primary;
    return (Node*)node;
}

Node*
makeTypeName(char* type_name) {
    TypeName* name = new TypeName();
    name->name     = type_name;
    return (Node*)name;
}

Node*
makeColumnDef(char* col_name, char* type_name) {
    ColumnDef* def = new ColumnDef();
    def->colname   = col_name;
    def->typeName  = type_name;
    return def;
}

Node*
makeSetParam(char* col_name, Node* value) {
    SetParam* param = new SetParam();
    param->colname  = col_name;
    param->value    = value;
    return param;
}
