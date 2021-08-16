#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lex.h"
#include "reader.h"
#include "global.h"
struct G {
    int i;
};

int
main(int argc, char* argv[]) {
    printf("sql parser %s, %s\n", argv[0], argv[1]);
    char* path   = argv[1];
    char* header = argv[2];
    char* source = argv[3];

    int location    = 0;
    const char* str = "select * from abc;";

    LexToken token = NULL;

    while ((token = GetLexerToken(str, &location)) != NULL) {
        if (token->tok != whitespace) {
            printf("token %3d (%3d,%3d) data (%s)\n", token->tok, token->location.line, token->location.offset, token->data);
        }
        FreeLexerToken(token);
    }


    char a[26] = "abcdefghijklmn";

    char* q = memchr(a, 'e', 8);

    printf("%c\n", *q);

    puts("jsklfdk\n");

    ParamsInit();

    reader("C:\\work\\mimidb\\sql.rule");

    int* p = malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        *(p+i) = i;
    }

    p = realloc(p, sizeof(int) * 20);
    for (int i = 0; i < 20; i++) {
        printf("%d\n", *p);
        p++;
    }


    return 0;
}
