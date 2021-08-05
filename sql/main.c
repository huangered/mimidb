#include <stdio.h>

int
main(int argc, char* argv[]) {
    printf("sql parser %s, %s", argv[0], argv[1]);
    char* path = argv[1];
    char* header = argv[2];
    char* source = argv[3];
    
    return 0;
}
