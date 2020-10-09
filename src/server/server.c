#include "server/server.h"
#include "mimi.h"
#include "foo.h"
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
}