#ifndef _parsenode_hpp_
#define _parsenode_hpp_

#include "node/node.h"

typedef int NodeList;

struct ExprStmt {
    NodeTag nodetag;
    char* key;
};

struct SelectStmt {
    NodeTag nodetag;
    char* relname;
    NodeList columns;
};

struct InsertStmt {
    NodeTag nodetag;
    char* relname;
    NodeList columns;
};

struct UpdateStmt {
    NodeTag nodetag;
    char* relname;
    NodeList columns;
    struct Node* where_cause;
};

struct AssignStmt {
    NodeTag nodetag;
    char* col_name;
    struct Node* value;
};

struct CreateTableStmt {
    NodeTag nodetag;
    char* relname;
    NodeList columns;
};

struct CreateTableParam {
    NodeTag nodetag;
    char* colname;
    char* type;
    int primary;
};

/*
 * index 描述
 */
struct CreateIndexStmt {
    NodeTag nodetag;
    char* relname;
    NodeList columns;
};

struct ParamStmt {
    NodeTag nodetag;
    char* key;
    char* type;
};

struct WhereStmt {
    NodeTag nodetag;
    NodeList columns;
};

struct OrderbyStmt {
    NodeTag nodetag;
    NodeList columns;
};

struct IntValue {
    NodeTag nodetag;
    int number;
};

struct StrValue {
    NodeTag nodetag;
    char* str;
};

struct TypeName {
    NodeTag nodetag;
    char* name;
    long typeOid;
};

struct ColumnDef {
    NodeTag nodetag;
    char* colname;
    char* typeName;
};

struct SetParam {
    NodeTag nodetag;
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

extern struct Node* mison_parse(const char* str);

#endif
