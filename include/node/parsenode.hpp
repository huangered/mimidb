#ifndef _parsenode_hpp_
#define _parsenode_hpp_

#include "node/node.hpp"
#include <vector>

using std::vector;

typedef vector<Node*>* NodeList;

struct ExprStmt : Node {
    char* key;
};

struct SelectStmt : Node {
    char* relname;
    NodeList columns;
};

struct InsertStmt : Node {
    char* relname;
    NodeList columns;
};

struct UpdateStmt : Node {
    char* relname;
    NodeList columns;
    Node* where_cause;
};

struct AssignStmt : Node {
    char* col_name;
    Node* value;
};

struct CreateTableStmt : Node {
    char* relname;
    NodeList columns;
};

struct CreateTableParam : Node {
    char* colname;
    char* type;
    int primary;
};

/*
 * index 描述
 */
struct CreateIndexStmt : Node {
    char* relname;
    NodeList columns;
};

struct ParamStmt : Node {
    char* key;
    char* type;
};

struct WhereStmt : Node {
    NodeList columns;
};

struct OrderbyStmt : Node {
    NodeList columns;
};

struct IntValue : Node {
    int number;
};

struct StrValue : Node {
    char* str;
};

struct TypeName : Node {
    char* name;
    long typeOid;
};

struct ColumnDef : Node {
    char* colname;
    char* typeName;
};

struct SetParam : Node {
    char* colname;
    Node* value;
};

Node* makeIntValue(int i);
Node* makeStrValue(char* str);
Node* makeExpr(char* key);
Node* makeParam(char* param1, char* param2);
Node* makeAssignStmt(char* col_name, Node* value);
Node* makeSelectStmt(char* tbl_name, NodeList cols, Node* whereStmt, Node* orderByStmt);
Node* makeInsertStmt(char* tbl_name, NodeList cols);
Node* makeUpdateStmt(char* tbl_name, NodeList cols, Node* where_cause);
Node* makeCreateTableStmt(char* tbl_name, NodeList cols);
Node* makeCreateTableParam(char* col_name, char* type, int primary);
Node* makeWhereStmt(NodeList cols);
Node* makeTypeName(char* type_name);
Node* makeColumnDef(char* col_name, char* type_name);
Node* makeOrderbyStmt(NodeList cols);
Node* makeSetParam(char* col_name, Node* value);

extern Node* mison_parse(const char* str);

#endif
