#include "mimi.h"
#include "foo.h"
#include "access/relcache.h"
#include "server/server.h"
#include "storage/bufmgr.h"
#include "util/mctx.h"

int
main(int argc, char* argv[]) {

	Startup();
    return 0;
}

void
Startup() {
	printf("start up mctx");
	MemoryContextInit();

	printf("start up buffer mgr");
	BufferInit();

	printf("start relation cache");
	RelationCacheInit();
}