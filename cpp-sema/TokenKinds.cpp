#include "TokenKinds.hpp"

Tok
GetTokByName(const std::string& name) {
    if (false) {
    }

#define TOK(X)                                                                                                         \
    else if (#X == name) {                                                                                             \
        return X;                                                                                                 \
    }
#include "tok.def"

    return unknown;
}