#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lex.h"
#include "reader.h"
#include "global.h"

int
main(int argc, char* argv[]) {
    printf("sql parser %s, %s\n", argv[0], argv[1]);
    char* path   = argv[1];
    char* header = argv[2];
    char* source = argv[3];

    int location    = 0;

    ParamsInit();

    reader("C:\\work\\mimidb\\sql-lex.rule");

    LexToken token = NULL;

    while ((token = GetLexerToken(data, &location)) != NULL) {
        if (token->tok != whitespace) {
            printf("token %3d (%3d,%3d) data (%s)\n", token->tok, token->location.line, token->location.offset,
                   token->data);
        }
        FreeLexerToken(token);
    }

    // generate symbol table
    
    // generate lr1

    // generate table

    // parse

    // output

    return 0;
}
