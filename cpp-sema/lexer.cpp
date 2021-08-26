﻿#include "lexer.hpp"
#include <cstring>
#include "c.tab.hpp"

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
}

LexToken
Lexer::GetLexerToken() {
    if (_cur >= _size) {
        return nullptr;
    }

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
        _cur++;
        return GetLexerToken();
    case ':':
        _cur++;
        return new LexTokenData(t_colon);
    case '%':
        return lexSign();
    case '{':
        return lexBlock();
    case '@':
        return lexPiont();
    case '<':
        _cur++;
        return new LexTokenData(t_less);
    case '>':
        _cur++;
        return new LexTokenData(t_greater);
    case '|':
        _cur++;
        return new LexTokenData(t_maybe);
    case ';':
        _cur++;
        return new LexTokenData(t_semicolon);
    }

    return nullptr;
}

int
Lexer::Yylex() {
    if (_cur >= _size) {
        return -1;
    }

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
        return lexIdentifier()->tok;
    case '\n':
    case ' ':
        _cur++;
        return GetLexerToken()->tok;
    case ':':
        _cur++;
        return t_colon;
    case '%':
        return lexSign()->tok;
    case '{':
        return lexBlock()->tok;
    case '@':
        return lexPiont()->tok;
    case '<':
        _cur++;
        return t_less;
    case '>':
        _cur++;
        return t_greater;
    case '|':
        _cur++;
        return t_maybe;
    case ';':
        _cur++;
        return t_semicolon;
    }

    return -1;
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

    LexToken token = new LexTokenData(t_identifier, p);

    Parser::yylval.node         = new NodeData{};
    Parser::yylval.node->_value = token->value;

    delete[] p;

    return token;
}

// 简化版
LexToken
Lexer::lexBlock() {
    int start = _cur + 1;
    int count = 0;
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

    LexToken token = new LexTokenData(t_block, p);
    delete[] p;

    Parser::yylval.node         = new NodeData{};
    Parser::yylval.node->_value = token->value;

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

    LexToken token = new LexTokenData(t_block, p);

    Parser::yylval.node         = new NodeData{};
    Parser::yylval.node->_value = token->value;

    delete[] p;

    if ("@token" == token->value) {
        token->tok = t_token;
    } else if ("@type" == token->value) {
        token->tok = t_type;
    } else if ("@param" == token->value) {
        token->tok = t_param;
    }
    return token;
}

LexToken
Lexer::lexSign() {
    yytokentype tok = t_sign;

    if (strncmp(_buf + _cur, "%code", 5) == 0) {
        tok = t_code;
        _cur += 5;
    } else if (strncmp(_buf + _cur, "%union", 6) == 0) {
        tok = t_union;
        _cur += 6;
    } else {
        _cur++;
    }

    LexToken token = new LexTokenData(tok);

    return token;
}
