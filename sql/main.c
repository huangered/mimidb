#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"

int
main(int argc, char* argv[]) {
    printf("sql parser %s, %s\n", argv[0], argv[1]);
    char* path   = argv[1];
    char* header = argv[2];
    char* source = argv[3];

    int location    = 0;
    const char* str = "select * from abc;";

    LexToken token = NULL;

    while ((token = GetLexerToken(str, strlen(str), &location)) != NULL) {
        if (token != whitespace) {
            printf("token %3d (%3d,%3d) data (%s)\n", token->tok, token->begin, token->end, token->data);
        }
        FreeLexerToken(token);
    }    

    return 0;
}
