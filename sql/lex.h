#ifndef _lex_h_
#define _lex_h_

#include "TokenKinds.h"

typedef struct location {
    int line;
    int offset;
} Location;

struct lexTokenData {
    Tok tok;
    char* data;
    int len;
    Location location;
};

typedef struct lexTokenData* LexToken;

LexToken GetLexerToken(const char* buf, int* location);
void FreeLexerToken(LexToken token);

#endif