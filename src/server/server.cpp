#include "mimi.hpp"
#include "foo.hpp"
#include "access/relcache.hpp"
#include "server/server.hpp"
#include "storage/bufmgr.hpp"
#include "util/mctx.hpp"

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
	//BufferInit();

	printf("start relation cache");
	RelationCacheInit();
}