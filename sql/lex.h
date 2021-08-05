#ifndef _lex_h_
#define _lex_h_

#include "TokenKinds.h"

struct lexTokenData {
    Tok tok;
    char* data;
    int begin;
    int end;
};

typedef struct lexTokenData* LexToken;

LexToken GetLexerToken(const char* buf, int size, int* location);

#endif;