#include "lexer.hpp"
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

SqlLexer::SqlLexer(const char* buf, int size)
    : _cur{ 0 }
    , _size{ size }
    , _buf{ buf } {
}

int
SqlLexer::yylex() {
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
        return lexIdentifier();
    case '\n':
    case ' ':
        _cur++;
        return yylex();
    case ':':
        _cur++;
        return t_colon;
    case '%':
        return lexSign();
    case '{':
        return lexBlock();
    case '@':
        return lexPiont();
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

int
SqlLexer::lexIdentifier() {
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

    Parser::yylval.node         = new NodeData{};
    Parser::yylval.node->_value = p;

    delete[] p;

    return t_identifier;
}

int
SqlLexer::lexBlock() {
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

    Parser::yylval.node         = new Node{};
    Parser::yylval.node->_value = p;

    delete[] p;

    return t_block;
}

int
SqlLexer::lexPiont() {
    yytokentype tok = t_block;

    if (strncmp(_buf + _cur, "@token", 6) == 0) {
        tok = t_token;
        _cur += 6;
    } else if (strncmp(_buf + _cur, "@type", 5) == 0) {
        tok = t_type;
        _cur += 5;
    } else if (strncmp(_buf + _cur, "@param", 6) == 0) {
        tok = t_param;
        _cur += 6;
    } else if (strncmp(_buf + _cur, "@start", 6) == 0) {
        tok = t_start_rule;
        _cur += 6;
    }

    return tok;
}

int
SqlLexer::lexSign() {
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

    return tok;
}

