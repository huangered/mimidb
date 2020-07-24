// mmdb.cpp : Defines the entry point for the application.
//

#include "server/server.h"
#include "access/cbtree.h"
#include "access/heap.h"
#include "util/mctx.h"
#include "storage/page.h"

int main(int argc, char* argv[])
{
	btbuildempty(NULL);
	Page page = palloc(8012);
	PageInit(page);
	heapbuildempty(NULL);
	return 0;
}
