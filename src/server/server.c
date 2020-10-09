#include "server/server.h"
#include "mimi.h"
#include "foo.h"

enum G {
	a,
	b,
	c,
};

int
main(int argc, char* argv[]) {
	
    printf("%d", NAME_INCLUDE);
	Startup();
	printf("%d", sizeof(enum G));
	printf("%d", sizeof(int));

    return 0;
}

void
Startup() {
	printf("start up");
}