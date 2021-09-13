#ifndef _lexer_hpp_
#define _lexer_hpp_

#include "c.tab.hpp"

class Lexer : public yylexer {
private:
    int _cur;
    int _size;
    const char* _buf;

public:
    Lexer(const char* buf, int size);
    virtual ~Lexer();
    virtual int yylex();
    virtual int pos();

private:
    int lexPiont();
    int lexIdentifier();
    int lexBlock();
    int lexSign();
    // handle #
    void lexPound();
};

#endif // !_lexer_hpp_
