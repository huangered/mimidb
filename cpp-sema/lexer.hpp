#ifndef _lexer_hpp_
#define _lexer_hpp_

#include <vector>
#include <string>
#include <map>

class LexTokenData {
public:
    int tok;
    std::string value;

    LexTokenData(int t) {
        tok = t;
    }

    LexTokenData(int t, std::string v) {
        tok   = t;
        value = v;
    }
};

typedef LexTokenData* LexToken;

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
    int Yylex();

private:
    LexToken lexPiont();
    LexToken lexIdentifier();
    LexToken lexBlock();
    LexToken lexSign();
};

#endif // !_lexer_hpp_
