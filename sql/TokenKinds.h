#ifndef _token_kinds_h_
#define _token_kinds_h_

enum tok
{
#define TOK(X) X,
#include "lex/tok.def"
    NUM_TOKENS,
};

typedef enum tok Tok;

Tok GetTokByName(const char* name);

#endif // ! _token_kinds_hpp_
