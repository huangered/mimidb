#include "lex.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static LexToken lexIdentifier(const char* _buf, int* _cur, int size);
static LexToken lexNumber(const char* _buf, int* _cur, int _size);
static LexToken lexString(const char* _buf, int* _cur, int _size);

LexToken
GetLexerToken(const char* buf, int size, int* location) {
    if (*location >= size) {
        return NULL;
    }

    int begin, end;
    Tok tok = unknown;

    char Char = buf[*location];
    begin     = *location;
    switch (Char) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return lexNumber(buf, location, size);
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
        return lexIdentifier(buf, location, size);
    case '(':
        tok = l_brace;
        break;
    case ')':
        tok = r_brace;
        break;
    case ' ':
        tok = whitespace;
        break;
    case '*':
        tok = star;
        break;
    case ';':
        tok = semicolon;
        break;
    case ',':
        tok = comma;
        break;
    case '.':
        tok = dot;
        break;
    case '/':
        tok = slash;
        break;
    case '+':
        tok = plus;
        break;
    case '-':
        tok = minus;
        break;
    case '=':
        tok = equal;
        break;
    case '"':
        return lexString(buf, location, size);
    }

    (*location)++;
    end = *location;

    LexToken token = malloc(sizeof(struct lexTokenData));
    assert(token);
    memset(token, 0, sizeof(struct lexTokenData));
    token->tok   = tok;
    token->data  = NULL;
    token->begin = begin;
    token->end   = end;

    return token;
}

void
FreeLexerToken(LexToken token) {
    free(token);
}

LexToken
lexIdentifier(const char* _buf, int* _cur, int _size) {
    int start = *_cur;
    int count = 0;
    for (; *_cur < _size; (*_cur)++) {
        char c = _buf[*_cur];
        if (c >= 'a' && c <= 'z') {
            count++;
        } else {
            break;
        }
    }

    char* p = malloc(sizeof(char) * (count + 1));

    strncpy(p, _buf + start, count);
    p[count] = '\0';

    LexToken token = malloc(sizeof(struct lexTokenData));
    token->tok     = identifier;
    token->data    = p;
    token->begin   = start;
    token->end     = *_cur;

    return token;
}

LexToken
lexNumber(const char* _buf, int* _cur, int _size) {
    int start = *_cur;
    int count = 0;
    for (; *_cur < _size; (*_cur)++) {
        char c = _buf[*_cur];
        if (c >= '0' && c <= '9') {
            count++;
        } else {
            break;
        }
    }

    char* p = malloc(sizeof(char) * (count + 1));
    assert(p);
    strncpy(p, _buf + start, count);
    p[count] = '\0';

    LexToken token = malloc(sizeof(struct lexTokenData));
    assert(p);
    token->tok   = number;
    token->data  = p;
    token->begin = start;
    token->end   = *_cur;

    return token;
}

LexToken
lexString(const char* _buf, int* _cur, int _size) {
    int start = *_cur;
    int count = 2;
    (*_cur)++; // skip first "
    for (; *_cur < _size; (*_cur)++) {
        char c = _buf[*_cur];
        if (c != '"') {
            count++;
        } else {
            break;
        }
    }
    (*_cur)++; // skip end "

    char* p = malloc(sizeof(char) * (count + 1));
    assert(p);
    strncpy(p, _buf + start, count);
    p[count] = '\0';

    LexToken token = malloc(sizeof(struct lexTokenData));
    assert(token);
    token->tok   = str;
    token->data  = p;
    token->begin = start;
    token->end   = *_cur;

    return token;
}