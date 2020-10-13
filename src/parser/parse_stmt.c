﻿#include "node/parsenode.h"
#include "util/mctx.h"

/* 
 * 解析create table sql
 */
Node*
makeCreateTableStmt(char* tbl_name, List* cols) {
	CreateTableStmt* stmt = palloc(sizeof(CreateTableStmt));
	stmt->nodetag = NT_CreateTableStmt;
	stmt->relname = tbl_name;
	stmt->columns = cols;

	return (Node*)stmt;
}

Node*
makeSelectStmt(char* tbl_name, List* cols) {
	printf("makeSelectStmt\n");
	SelectStmt* stmt = (SelectStmt*)palloc(sizeof(SelectStmt));
	stmt->nodetag = NT_SelectStmt;
	stmt->relname = tbl_name;
	stmt->columns = cols;
	return (Node*)stmt;
}

Node*
makeInsertStmt(char* tbl_name, List* cols) {
	printf("makeInsertStmt\n");
	InsertStmt* stmt = (InsertStmt*)palloc(sizeof(InsertStmt));
	stmt->nodetag = NT_InsertStmt;
	stmt->relname = tbl_name;
	stmt->columns = cols;
	return (Node*)stmt;
}

Node*
makeUpdateStmt(char* tbl_name, List* cols, Node* where_cause) {
	UpdateStmt* stmt = (UpdateStmt*)palloc(sizeof(UpdateStmt));
	stmt->nodetag = NT_UpdateStmt;
	stmt->relname = tbl_name;
	stmt->columns = cols;
	stmt->where_cause = where_cause;
	return (Node*)stmt;
}

/*
update sql的赋值语句 a='abcd' or a=123
*/
Node*
makeAssignStmt(char* col_name, Node* value) {
	AssignStmt* stmt = (AssignStmt*)palloc(sizeof(AssignStmt));
	stmt->nodetag = NT_AssignStmt;
	stmt->col_name = col_name;
	stmt->value = value;
	return (Node*)stmt;
}


/*
解析where从句
*/
Node*
makeWhereStmt(List* cols) {
	WhereStmt* stmt = (WhereStmt*)palloc(sizeof(WhereStmt));
	stmt->nodetag = NT_WhereStmt;
	stmt->columns = cols;

	return (Node*)stmt;
}
