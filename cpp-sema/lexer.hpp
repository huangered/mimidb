#ifndef _lexer_hpp_
#define _lexer_hpp_

#include <vector>
#include <string>
#include <map>

#include "TokenKinds.hpp"

class LexTokenData {
public:
    Tok tok;
    std::string value;
};

typedef LexTokenData* LexToken;

#define EndLexToken (new LexTokenData{ Eof, "eof" })

struct LexerOption {
    bool skipWhiteSpace;
};

class Lexer {
private:
    int _cur;
    int _size;
    const char* _buf;
    

public:
    Lexer(const char* buf, int size);

    LexToken GetLexerToken();

private:
    LexToken lexPiont();
    LexToken lexIdentifier();
    LexToken lexBlock();
    LexToken lexSign();
};

#endif // !_lexer_hpp_
