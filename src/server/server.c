#include "server/server.h"
#include "mimi.h"
#include "foo.h"

int
main(int argc, char* argv[]) {
	
    printf("%d", NAME_INCLUDE);
	Startup();

    return 0;
}

void
Startup() {
	printf("start up");
}