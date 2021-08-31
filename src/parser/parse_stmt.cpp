#include "node/parsenode.hpp"
/*
 * 解析create table sql
 */
Node*
makeCreateTableStmt(char* tbl_name, vector<Node*>* cols) {
  CreateTableStmt* stmt = new CreateTableStmt();
    stmt->nodetag         = NT_CreateTableStmt;
    stmt->relname         = tbl_name;
    stmt->columns         = cols;

    return (Node*)stmt;
}

Node*
makeSelectStmt(char* tbl_name, vector<Node*>* cols) {
  SelectStmt* stmt = new SelectStmt();
    stmt->nodetag    = NT_SelectStmt;
    stmt->relname    = tbl_name;
    stmt->columns    = cols;
    return (Node*)stmt;
}

Node*
makeInsertStmt(char* tbl_name, vector<Node*>* cols) {
  InsertStmt* stmt = new InsertStmt();
    stmt->nodetag    = NT_InsertStmt;
    stmt->relname    = tbl_name;
    stmt->columns    = cols;
    return (Node*)stmt;
}

Node*
makeUpdateStmt(char* tbl_name, vector<Node*>* cols, Node* where_cause) {
  UpdateStmt* stmt  = new UpdateStmt();
    stmt->nodetag     = NT_UpdateStmt;
    stmt->relname     = tbl_name;
    stmt->columns     = cols;
    stmt->where_cause = where_cause;
    return (Node*)stmt;
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
    return (Node*)stmt;
}

/*
解析where从句
*/
Node*
makeWhereStmt(vector<Node*>* cols) {
  WhereStmt* stmt = new WhereStmt();
    stmt->nodetag   = NT_WhereStmt;
    stmt->columns   = cols;

    return (Node*)stmt;
}

Node*
mison_parse(const char* str) {
  return nullptr;
}
