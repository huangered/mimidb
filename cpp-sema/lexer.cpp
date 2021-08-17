#include "lexer.hpp"

static bool
isCharacter(char c) {
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    if (c == '_') {
        return true;
    }
    return false;
}


Lexer::Lexer(const char* buf, int size)
    : _cur{ 0 }
    , _size{ size }
    , _buf{ buf } {
#define KEYWORD(X, Y) _meta[#X] = Tok::kw_##X;
#include "tok.def"
}

LexToken
Lexer::GetLexerToken() {
    if (_cur >= _size) {
        return nullptr;
    }
    Tok tok{ Tok::unknown };
    char Char = _buf[_cur];

    switch (Char) {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
        return lexIdentifier();
    case '\n':
    case ' ':
        tok = Tok::whitespace;
        break;
    case ':':
        tok = Tok::t_colon;
        break;
    case '%':
        tok = Tok::t_sign;
        break;
    case '{':
        return lexBlock();
    case '@':
        return lexPiont();
    }

    _cur++;
    LexToken token = new LexTokenData{ tok };
    return token;
}

LexToken
Lexer::lexIdentifier() {
    int start = _cur;
    int count = 0;
    for (; _cur < _size; _cur++) {
        char c = _buf[_cur];
        if (isCharacter(c)) {
            count++;
        } else {
            break;
        }
    }

    char* p = new char[count + 1];
    strncpy(p, _buf + start, count);
    p[count] = '\0';

    LexToken token = new LexTokenData{ Tok::t_identifier, p };

    delete[] p;

    if (_meta.count(token->name) > 0) {
        token->tok = _meta[token->name];
    }

    return token;
}


// 简化版
LexToken
Lexer::lexBlock() {
    int start = _cur;
    int count = 2;
    _cur++; // skip first "
    for (; _cur < _size; _cur++) {
        char c = _buf[_cur];
        if (c != '}') {
            count++;
        } else {
            break;
        }
    }
    _cur++; // skip end "

    char* p = new char[count + 1];
    
    strncpy(p, _buf + start, count);
    p[count] = '\0';

    LexToken token = new LexTokenData{ Tok::t_block, p };
    delete[] p;

    return token;
}

LexToken
Lexer::lexPiont() {
    int start = _cur;
    int count = 1;
    _cur++; // skip first "
    for (; _cur < _size; _cur++) {
        char c = _buf[_cur];
        if (c != ' ') {
            count++;
        } else {
            break;
        }
    }

    char* p = new char[count + 1];

    strncpy(p, _buf + start, count);
    p[count] = '\0';

    LexToken token = new LexTokenData{ Tok::t_block, p };
    delete[] p;

    if ("@token" == token->name) {
        token->tok = Tok::t_token;
    } else if ("@type" == token->name) {
        token->tok = Tok::t_type;
    } else {
        token->tok = unknown;
    }
    return token;
}