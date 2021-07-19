#ifndef  _token_kinds_hpp_
#define _token_kinds_hpp_

enum Tok : unsigned int
{
#define TOK(X) X,
#include "lex/tok.def"
    NUM_TOKENS,
};

typedef std::vector<Tok> TokList;

#endif // ! _token_kinds_hpp_


