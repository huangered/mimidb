#ifndef _token_kinds_hpp_
#define _token_kinds_hpp_

#include <vector>
#include <string>

enum Tok : unsigned int
{
#define TOK(X) X,
#include "tok.def"
    NUM_TOKENS,
};

typedef std::vector<Tok> TokList;

Tok GetTokByName(const std::string& name);

#endif // ! _token_kinds_hpp_
