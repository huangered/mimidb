#include "node/parsenode.h"
#include "util/mctx.h"

Node*
makeCreateTableStmt(char* tbl_name, List* cols) {
	CreateTableStmt* stmt = palloc(sizeof(CreateTableStmt));
	stmt->nodetag = NT_CreateTableStmt;
	stmt->relname = tbl_name;
	stmt->columns = cols;

	return stmt;
}

Node*
makeSelectStmt(char* tbl_name, List* cols) {
	printf("makeSelectStmt\n");
	SelectStmt* stmt = (SelectStmt*)malloc(sizeof(SelectStmt));
	stmt->nodetag = NT_SelectStmt;
	stmt->relname = tbl_name;
	stmt->columns = cols;
	return (Node*)stmt;
}

Node*
makeInsertStmt(char* tbl_name, List* cols) {
	printf("makeInsertStmt\n");
	InsertStmt* stmt = (InsertStmt*)malloc(sizeof(InsertStmt));
	stmt->nodetag = NT_InsertStmt;
	stmt->relname = tbl_name;
	stmt->columns = cols;
	return (Node*)stmt;
}

Node*
makeUpdateStmt(char* tbl_name) {
	return NULL;
}