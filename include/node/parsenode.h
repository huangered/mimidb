#ifndef _parsenode_hpp_
#define _parsenode_hpp_

#include "node/node.h"

typedef int NodeList;

struct ExprStmt {
    char* key;
};

struct SelectStmt {
    char* relname;
    NodeList columns;
};

struct InsertStmt {
    char* relname;
    NodeList columns;
};

struct UpdateStmt {
    char* relname;
    NodeList columns;
    struct Node* where_cause;
};

struct AssignStmt {
    char* col_name;
    struct Node* value;
};

struct CreateTableStmt {
    char* relname;
    NodeList columns;
};

struct CreateTableParam {
    char* colname;
    char* type;
    int primary;
};

/*
 * index 描述
 */
struct CreateIndexStmt {
    char* relname;
    NodeList columns;
};

struct ParamStmt {
    char* key;
    char* type;
};

struct WhereStmt {
    NodeList columns;
};

struct OrderbyStmt {
    NodeList columns;
};

struct IntValue {
    int number;
};

struct StrValue {
    char* str;
};

struct TypeName {
    char* name;
    long typeOid;
};

struct ColumnDef {
    char* colname;
    char* typeName;
};

struct SetParam {
    char* colname;
    struct Node* value;
};

struct Node* makeIntValue(int i);
struct Node* makeStrValue(char* str);
struct Node* makeExpr(char* key);
struct Node* makeParam(char* param1, char* param2);
struct Node* makeAssignStmt(char* col_name, struct Node* value);
struct Node* makeSelectStmt(char* tbl_name, NodeList cols, struct Node* whereStmt, struct Node* orderByStmt);
struct Node* makeInsertStmt(char* tbl_name, NodeList cols);
struct Node* makeUpdateStmt(char* tbl_name, NodeList cols, struct Node* where_cause);
struct Node* makeCreateTableStmt(char* tbl_name, NodeList cols);
struct Node* makeCreateTableParam(char* col_name, char* type, int primary);
struct Node* makeWhereStmt(NodeList cols);
struct Node* makeTypeName(char* type_name);
struct Node* makeColumnDef(char* col_name, char* type_name);
struct Node* makeOrderbyStmt(NodeList cols);
struct Node* makeSetParam(char* col_name, struct Node* value);

extern Node* mison_parse(const char* str);

#endif
