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
    case '0':
    case '1':
        return lexNumber();
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
    case ';':
        _cur++;
        return semicolon;
    case '*':
        _cur++;
        return star;
    case '(':
        _cur++;
        return l_paran;
    case ')':
        _cur++;
        return r_paran;
    case ',':
        _cur++;
        return comma;
    case '\'':
        return lexText();
    case '.':
        _cur++;
        return dot;
    case '=':
        _cur++;
        return equal;
    }

    printf("find unknown\n");

    return -1;
}

int
SqlLexer::lexText() {
    _cur++;
    int start = _cur;
    int count = 0;
    for (; _cur < _size; _cur++) {
        char c = _buf[_cur];
        if (c == '\'') {
            break;
        } else {
            count++;
        }
    }
    _cur++;

    char* p = new char[count + 1];
    strncpy(p, _buf + start, count);
    p[count] = '\0';

    return t_text;
}

int
SqlLexer::lexIdentifier() {
    yytokentype token = t_id;
    int start         = _cur;
    int count         = 0;
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
    // check identifier table
    if (strcmp(p, "create") == 0) {
        token = CREATE;
    } else if (strcmp(p, "table") == 0) {
        token = TABLE;
    } else if (strcmp(p, "select") == 0) {
        token = SELECT;
    } else if (strcmp(p, "from") == 0) {
        token = FROM;
    } else if (strcmp(p, "update") == 0) {
        token = UPDATE;
    } else if (strcmp(p, "into") == 0) {
        token = INTO;
    } else if (strcmp(p, "insert") == 0) {
        token = INSERT;
    } else if (strcmp(p, "values") == 0) {
        token = VALUES;
    } else if (strcmp(p, "delete") == 0) {
        token = DELETE;
    } else if (strcmp(p, "set") == 0) {
        token = SET;
    } else if (strcmp(p, "where") == 0) {
        token = WHERE;
    } else if (strcmp(p, "orderby") == 0) {
        token = ORDERBY;
    } else if (strcmp(p, "begin") == 0) {
        token = BEGIN;
    } else if (strcmp(p, "commit") == 0) {
        token = COMMIT;
    } else if (strcmp(p, "and") == 0) {
        token = AND;
    } else if (strcmp(p, "or") == 0) {
        token = OR;
    }

    // default text
    if (token == t_id) {
        Parser::yylval.str = p;
    } else {
        delete[] p;
    }

    return token;
}

int
SqlLexer::lexNumber() {
    int start = _cur;
    int count = 0;
    for (; _cur < _size; _cur++) {
        char c = _buf[_cur];
        if (c >= '0' && c <= '9') {
            count++;
        } else {
            break;
        }
    }

    char* p = new char[count + 1];
    strncpy(p, _buf + start, count);
    p[count] = '\0';

    Parser::yylval.num = atoi(p);

    delete[] p;

    return t_number;
}
