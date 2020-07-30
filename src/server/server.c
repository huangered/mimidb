// mmdb.cpp : Defines the entry point for the application.
//

#include "server/server.h"
#include "access/cbtree.h"
#include "access/heap.h"
#include "util/mctx.h"
#include "storage/page.h"
#include "port/shmem.h"

int main(int argc, char* argv[])
{
	btbuildempty(NULL);
	Page page = palloc(8012);
	PageInit(page, 8012);
	heapbuildempty(NULL);

	char* ptr = (char*)shmem_init(100);
	*ptr = '1';
	shmem_close();


	int* p = (int*)malloc(sizeof(int) * 10);
	memset(p, 0, sizeof(int)*10);
	for (int i = 0; i < 10; i++) {
		printf("%d\r\n", *(p + i));
	}
	return 0;
}
