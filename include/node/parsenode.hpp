#ifndef _PARSENODE_H_
#define _PARSENODE_H_

#include "node/node.hpp"
#include "util/list.hpp"

typedef struct NodeWrap {
	Node* node;
} NodeWrap;

typedef struct ExprStmt {
	NodeTag nodetag;
	char* key;
} ExprStmt;

typedef struct SelectStmt {
	NodeTag nodetag;
	char* relname;
	List* columns;
} SelectStmt;

typedef struct InsertStmt {
	NodeTag nodetag;
	char* relname;
	List* columns;
} InsertStmt;

typedef struct UpdateStmt {
	NodeTag nodetag;
	char* relname;
	List* columns;
	Node* where_cause;
} UpdateStmt;

typedef struct AssignStmt {
	NodeTag nodetag;
	char* col_name;
	Node* value;
} AssignStmt;

typedef struct CreateTableStmt {
	NodeTag nodetag;
	char* relname;
	List* columns;
} CreateTableStmt;

typedef struct CreateTableParam {
	NodeTag nodetag;
	char* colname;
	char* type;
	bool primary;
} CreateTableParam;

/*
index 描述
*/
typedef struct CreateIndexStmt {
	NodeTag nodetag;
	char* relname;
	List* columns;
} CreateIndexStmt;

typedef struct ParamStmt {
	NodeTag nodetag;
	char* key;
	char* type;
} ParamStmt;

typedef struct WhereStmt {
	NodeTag nodetag;
	List* columns;
} WhereStmt;

typedef struct IntValue {
	NodeTag nodetag;
	int number;
} IntValue;

typedef struct StrValue {
	NodeTag nodetag;
	char* str;
} StrValue;

typedef struct TypeName {
	NodeTag nodetag;
	char* name;
	Oid typeOid;
} TypeName;

typedef struct ColumnDef {
	NodeTag nodetag;
	char* colname;
	TypeName* typeName;
} ColumnDef;


extern "C" {
	Node* makeIntValue(int i);
	Node* makeStrValue(char* str);
	Node* makeExpr(char* key);
	Node* makeParam(char* param1, char* param2);
	Node* makeAssignStmt(char* col_name, Node* value);
	Node* makeSelectStmt(char* tbl_name, List* cols);
	Node* makeInsertStmt(char* tbl_name, List* cols);
	Node* makeUpdateStmt(char* tbl_name, List* cols, Node* where_cause);
	Node* makeCreateTableStmt(char* tbl_name, List* cols);
	Node* makeCreateTableParam(char* col_name, char* type, bool primary);
	Node* makeWhereStmt(List* cols);
	NodePtr makeTypeName(char* type_name);
	NodePtr makeColumnDef(char* col_name, TypeName* type_name, bool primary);
}
#endif