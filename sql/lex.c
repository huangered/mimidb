#include "lex.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static LexToken lexIdentifier(const char* _buf, int* _cur);
static LexToken lexNumber(const char* _buf, int* _cur);
static LexToken lexString(const char* _buf, int* _cur);
static LexToken lexBlock(const char* _buf, int* _cur);

LexToken
GetLexerToken(const char* buf, int* location) {
    if (*location >= strlen(buf)) {
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
        return lexNumber(buf, location);
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
        return lexIdentifier(buf, location);
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
        return lexString(buf, location);
    case '{':
        return lexBlock(buf, location);
    }

    (*location)++;
    end = *location;

    LexToken token = malloc(sizeof(struct lexTokenData));
    assert(token);
    memset(token, 0, sizeof(struct lexTokenData));
    token->tok             = tok;
    token->data            = NULL;
    token->len             = begin - end;
    token->location.line   = 0;
    token->location.offset = begin;

    return token;
}

void
FreeLexerToken(LexToken token) {
    free(token);
}

LexToken
lexIdentifier(const char* _buf, int* _cur) {
    int start = *_cur;
    int count = 0;
    for (; *_cur < strlen(_buf); (*_cur)++) {
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

    LexToken token         = malloc(sizeof(struct lexTokenData));
    token->tok             = identifier;
    token->data            = p;
    token->len             = start - *_cur;
    token->location.line   = 0;
    token->location.offset = start;

    return token;
}

LexToken
lexNumber(const char* _buf, int* _cur) {
    int start = *_cur;
    int count = 0;
    for (; *_cur < strlen(_buf); (*_cur)++) {
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
    token->tok             = number;
    token->data            = p;
    token->len             = start - *_cur;
    token->location.line   = 0;
    token->location.offset = start;

    return token;
}

LexToken
lexString(const char* _buf, int* _cur) {
    int start = *_cur;
    int count = 2;
    (*_cur)++; // skip first "
    for (; *_cur < strlen(_buf); (*_cur)++) {
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
    token->tok             = str;
    token->data            = p;
    token->len             = start - *_cur;
    token->location.line   = 0;
    token->location.offset = start;

    return token;
}

// 简化版
LexToken
lexBlock(const char* _buf, int* _cur) {
    int start = *_cur;
    int count = 2;
    (*_cur)++; // skip first "
    for (; *_cur < strlen(_buf); (*_cur)++) {
        char c = _buf[*_cur];
        if (c != '}') {
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
    token->tok             = str;
    token->data            = p;
    token->len             = start - *_cur;
    token->location.line   = 0;
    token->location.offset = start;

    return token;
}