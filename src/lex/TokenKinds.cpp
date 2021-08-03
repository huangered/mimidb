#include "lex/TokenKinds.hpp"

Tok
GetTokByName(const std::string& name) {
    if (name.empty()) {
        return Tok::unknown;
    }

#define TOK(X)                                                                                                         \
    else if (#X == name) {                                                                                             \
        return Tok::X;                                                                                                 \
    }
#include "lex/tok.def"

    return Tok::unknown;
}