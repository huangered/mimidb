#ifndef _lexer_hpp_
#define _lexer_hpp_

#include <vector>
#include <string>
#include <map>

#include "TokenKinds.hpp"

class LexTokenData {
public:
    Tok tok;
    std::string name;
};

typedef LexTokenData* LexToken;

#define EndLexToken (new LexTokenData{ Tok::Eof, "eof" })

struct LexerOption {
    bool skipWhiteSpace;
};

class Lexer {
private:
    int _cur;
    int _size;
    const char* _buf;
    std::map<std::string, Tok> _meta;

public:
    Lexer(const char* buf, int size);

    LexToken GetLexerToken();

private:
    LexToken lexNumber();
    LexToken lexIdentifier();
    LexToken lexString();
};

#endif // !_lexer_hpp_
