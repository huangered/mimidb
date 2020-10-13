#include "commands/create.h"
#include "top/utility.h"
#include "parser/parse_utilitycmd.h"
#include "util/list.h"
/*
处理create table sql
*/
void
ProcessUtility(Node* pstmt) {
	switch (pstmt->nodetag)
	{
	case NT_CreateTableStmt:
	{
		List* stmts = NULL;

		// 拆解create table sql
		stmts = transformCreateStmt((CreateTableStmt*)pstmt);

		Node* stmt = (Node*)stmts->head;
		if (stmt->nodetag == NT_CreateTableStmt) {
			DefineRelation((CreateTableStmt*)stmt);
		}

		// process other.
		// todo:
	}
	break;
	}
}