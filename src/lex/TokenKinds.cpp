#include "lex/TokenKinds.hpp"
#include <map>

Tok
GetTokByName(std::string name) {
    std::map<std::string, Tok> data;

    #define TOK(X) data[#X]=X;
    #include "lex/tok.def"
    if (data.count(name) == 0) {
        exit(100);
    }
    return data[name];
}