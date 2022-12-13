#include <cstdio>
#include "node/parsenode.h"

int
main(int argc, char* argv[]) {

    printf("hello mimi db!\n");

    char str[256];

    while (true) {
        printf("enter sql:\n");
        fgets(str, 256, stdin);

        printf("you enter:%s\n", str);

        Node* raw = mison_parse(str);

        if (raw != nullptr) {
            printf("%p\n", raw);
            delete raw;
        }
    }

    return 0;
}
