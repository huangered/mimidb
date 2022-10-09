#include "node/parsenode.hpp"
#include "c.tab.hpp"
#include "lexer.hpp"
#include <cstring>
/*
 * 解析create table sql
 */
Node*
makeCreateTableStmt(char* tbl_name, NodeList cols) {
    CreateTableStmt* stmt = new CreateTableStmt();
    stmt->nodetag         = NT_CreateTableStmt;
    stmt->relname         = tbl_name;
    stmt->columns         = cols;

    return stmt;
}

Node*
makeSelectStmt(char* tbl_name, NodeList cols, Node* whereStmt, Node* orderByStmt) {
    SelectStmt* stmt = new SelectStmt();
    stmt->nodetag    = NT_SelectStmt;
    stmt->relname    = tbl_name;
    stmt->columns    = cols;
    if (whereStmt == nullptr) {
        printf("where stmt is nullptr\n");
    }
    return stmt;
}

Node*
makeInsertStmt(char* tbl_name, NodeList cols) {
    InsertStmt* stmt = new InsertStmt();
    stmt->nodetag    = NT_InsertStmt;
    stmt->relname    = tbl_name;
    stmt->columns    = cols;
    return stmt;
}

Node*
makeUpdateStmt(char* tbl_name, vector<Node*>* cols, Node* where_cause) {
    UpdateStmt* stmt  = new UpdateStmt();
    stmt->nodetag     = NT_UpdateStmt;
    stmt->relname     = tbl_name;
    stmt->columns     = cols;
    stmt->where_cause = where_cause;
    return stmt;
}

/*
update sql的赋值语句 a='abcd' or a=123
*/
Node*
makeAssignStmt(char* col_name, Node* value) {
    AssignStmt* stmt = new AssignStmt();
    stmt->nodetag    = NT_AssignStmt;
    stmt->col_name   = col_name;
    stmt->value      = value;
    return stmt;
}

/*
解析where从句
*/
Node*
makeWhereStmt(vector<Node*>* cols) {
    WhereStmt* stmt = new WhereStmt();
    stmt->nodetag   = NT_WhereStmt;
    stmt->columns   = cols;

    return stmt;
}

Node*
makeOrderbyStmt(vector<Node*>* cols) {
    OrderbyStmt* stmt = new OrderbyStmt();

    return stmt;
}

Node*
mison_parse(const char* str) {
    Parser p(new SqlLexer(str, strlen(str)));
    Node* node = p.parse();

    return node;
}
