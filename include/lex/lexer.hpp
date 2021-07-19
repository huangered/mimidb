#ifndef _lexer_hpp_
#define _lexer_hpp_

#include <vector>
#include <string>
#include <map>

#include "lex/TokenKinds.hpp"

#define IsLex(id)  (id > 0)
#define IsSema(id) (!IsLex(id))

struct LexTokenData {
    Tok tok;
    std::string name;
    
    int Compare(const LexTokenData& token);
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
    std::map<std::string, Tok> _meta;

public:
    Lexer(const char* buf, int size);

    LexToken GetLexerToken();
private:
    LexToken lexNumber();
    LexToken lexIdentifier();
};

#endif // !_lexer_hpp_
