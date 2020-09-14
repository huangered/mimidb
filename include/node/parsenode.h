#ifndef _PARSENODE_H_
#define _PARSENODE_H_

#include "node/node.h"
#include "util/list.h"

typedef struct SelectStmt {
	NodeTag nodetag;
	char* relname;
	List column;
} SelectStmt;

typedef struct CreateStmt {
	NodeTag nodetag;
	char* relname;
	List column;
} CreateStmt;

#endif