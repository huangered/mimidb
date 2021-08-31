#ifndef _parsenode_hpp_
#define _parsenode_hpp_

#include "node/node.hpp"
#include <vector>

using std::vector;

class ExprStmt : public Node {
public:
    char* key;
};

class SelectStmt : public Node {
public:
    char* relname;
    vector<Node*>* columns;
};

class InsertStmt : public Node {
public:
    char* relname;
    vector<Node*>* columns;
};

class UpdateStmt : public Node {
public:
    char* relname;
    vector<Node*>* columns;
    Node* where_cause;
};

class AssignStmt : public Node {
public:
    char* col_name;
    Node* value;
};

class CreateTableStmt : public Node {
public:
    char* relname;
    vector<Node*>* columns;
};

class CreateTableParam : public Node {
public:
    char* colname;
    char* type;
    int primary;
};

/*
index 描述
*/
class CreateIndexStmt : public Node {
public:
    char* relname;
    vector<Node*>* columns;
};

class ParamStmt : public Node {
public:
    char* key;
    char* type;
};

class WhereStmt : public Node {
public:
    vector<Node*>* columns;
};

class IntValue : public Node {
public:
    int number;
};

class StrValue : public Node {
public:
    char* str;
};

class TypeName : public Node {
public:
    char* name;
    long typeOid;
};

class ColumnDef : public Node {
public:
    char* colname;
    TypeName* typeName;
    int primary;
};

Node* makeIntValue(int i);
Node* makeStrValue(char* str);
Node* makeExpr(char* key);
Node* makeParam(char* param1, char* param2);
Node* makeAssignStmt(char* col_name, Node* value);
Node* makeSelectStmt(char* tbl_name, vector<Node*>* cols);
Node* makeInsertStmt(char* tbl_name, vector<Node*>* cols);
Node* makeUpdateStmt(char* tbl_name, vector<Node*>* cols, Node* where_cause);
Node* makeCreateTableStmt(char* tbl_name, vector<Node*>* cols);
Node* makeCreateTableParam(char* col_name, char* type, int primary);
Node* makeWhereStmt(vector<Node*>* cols);
Node* makeTypeName(char* type_name);
Node* makeColumnDef(char* col_name, TypeName* type_name, int primary);

#endif
