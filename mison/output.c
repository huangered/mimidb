#include "output.hpp"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "reader.hpp"
#include "symtab.hpp"
#include "debug.hpp"

Output::Output(SemaParser* _p)
    : parser{ _p } {
}

void
Output::SetCode(std::string b) {
    codeBlock = b;
}
void
Output::SetUnion(std::string b) {
    unionBlock = b;
}

void
Output::SetOther(std::string b) {
    other = b;
}

void
Output::SetParam(std::string p) {
    param = p;
}

void
Output::OutputFile(const char* fout) {
    writeM4(fout);
};

FILE*
OpenFile(const char* file, const char* mode) {
    FILE* f = fopen(file, mode);
    assert(f);
    return f;
}

char*
ReadFile(FILE* f) {
    int r   = fseek(f, 0, SEEK_END);
    long sz = ftell(f);

    char* buf = new char[sz + 1];
    memset(buf, 0, sz + 1);
    fseek(f, 0, SEEK_SET);

    fread(buf, sizeof(char), sz, f);

    return buf;
}

void
WriteFile(FILE* f, const char* buf) {
    int len = strlen(buf);
    fprintf(f, "%s", buf);
}

void
CloseFile(FILE* f) {
    fclose(f);
}

void
Output::writeM4(const char* fout) {
    char* f = new char[256];
    memset(f, 0, 256);
    memcpy(f, fout, strlen(fout));
    memcpy(f + strlen(fout), "value.m4", 8);
#ifdef _log_
    printf("value.m4 path, %s\n", f);
#endif
    FILE* fd = OpenFile(f, "w");

    writeCode(fd);

    writeUnion(fd);

    writeTokEnum(fd);

    writeOther(fd);

    writeConst(fd);

    CloseFile(fd);

    memcpy(f + strlen(fout), "rules.m4", 8);

#ifdef _log_
    printf("rules.m4 path, %s\n", f);
#endif

    fd = OpenFile(f, "w");

    delete[] f;

    writeRule(fd);

    CloseFile(fd);
}

void
Output::writeCode(FILE* f) {
    int len   = codeBlock.length() + 50;
    char* buf = new char[len];
    memset(buf, 0, len);
    sprintf(buf, "define(CodeBody, `%s')\n", codeBlock.c_str());
    WriteFile(f, buf);
    delete[] buf;
}
void
Output::writeUnion(FILE* f) {
    int len   = unionBlock.length() + 50;
    char* buf = new char[len];
    memset(buf, 0, len);
    sprintf(buf, "define(UnionBody,`%s')\n", unionBlock.c_str());
    WriteFile(f, buf);
    delete[] buf;
}

void
Output::writeTokEnum(FILE* f) {
    std::vector<Symbol> d;

    for (auto it = Symtab::_data.begin(); it != Symtab::_data.end(); it++) {
        if (it->second->clazz == token && it->second->id > 1) {
            d.push_back(it->second);
        }
    }

    std::sort(d.begin(), d.end(), [](Symbol l, Symbol r) -> bool { return l->id < r->id; });

    WriteFile(f, "define(TokenBody, `");
    for (auto it = d.begin(); it != d.end(); it++) {
        char* buf = new char[256];
        sprintf(buf, "    %15s = %3d,\n", (*it)->name.c_str(), (*it)->id);
        WriteFile(f, buf);
        delete[] buf;
    }

    WriteFile(f, "')\n");
}

void
Output::writeOther(FILE* f) {
    int len   = other.length() + 50;
    char* buf = new char[len];
    memset(buf, 0, len);
    sprintf(buf, "define(CodeBody2,`%s')\n", other.c_str());
    WriteFile(f, buf);
    delete[] buf;
}

void
Output::writeRule(FILE* f) {
    /*
    include(`foreach.m4')
    define(`_case', `    case $1:
// line $3
            {
              $2
            }
            break;
    ')dnl
    define(`_cat', `$1$2')dnl

    foreach(`x',
    `(
    `(`0', `vara')',
    `(`1', `item.asdf = makeNmode(djsfjl.af[0]);')',
    `(`2', `varc')',
    )',
    `_cat(`_case', x)')dnl
    */
    WriteFile(f, "include(`foreach.m4')\n");
    WriteFile(f, "define(`_case', `    case $1:\n");
    WriteFile(f, "        // line $3\n");
    WriteFile(f, "        { $2 }\n");
    WriteFile(f, "        break;\n");
    WriteFile(f, "')dnl\n");
    WriteFile(f, "define(`_cat', `$1$2$3')dnl\n");

    WriteFile(f, "foreach(`x',\n");
    WriteFile(f, "`(\n");

    for (int i{ 0 }; i < Rules.size(); i++) {
        std::string g = parser->funcReplace(Rules[i]);

        char* buf = new char[256];
        memset(buf, 0, 256);
        sprintf(buf, "`(`%d',`%s', `%d')',\n", i, g.c_str(), i * 20);

        WriteFile(f, buf);

        delete[] buf;
    }

    WriteFile(f, ")',\n");
    WriteFile(f, "`_cat(`_case', x)')dnl\n");
}

void
Output::writeConst(FILE* f) {
    char* buf = new char[256];
    memset(buf, 0, 256);
    sprintf(buf, "define(NUMNTERM, `%d')\n", Symtab::nnterm());
    WriteFile(f, buf);

    memset(buf, 0, 256);
    sprintf(buf, "define(NUMTOKEN, `%d')\n", Symtab::ntoken());
    WriteFile(f, buf);

    memset(buf, 0, 256);
    sprintf(buf, "define(NUMSTATE, `%d')\n", parser->_stateList->Size());
    WriteFile(f, buf);

    // data action table
    memset(buf, 0, 256);
    WriteFile(f, "define(DATA_ACTION, `\n");
    for (int i{ 0 }; i < parser->_stateList->Size(); i++) {
        WriteFile(f, "{");
        for (int j{ 0 }; j < Symtab::ntoken(); j++) {
            Record record = parser->_actionTable->Find(i, j);
            if (record != nullptr) {
                if (record->acc) {
                    sprintf(buf, "10000,");
                } else if (record->state) {
                    sprintf(buf, "%d,", record->id);
                } else {
                    sprintf(buf, "-%d,", record->id);
                }
                WriteFile(f, buf);
            } else {
                WriteFile(f, "MAX_ID,");
            }
        }
        WriteFile(f, "},\n");
    }
    WriteFile(f, "')\n");

    // data goto table

    memset(buf, 0, 256);
    WriteFile(f, "define(DATA_GOTO, `\n");
    for (int i{ 0 }; i < parser->_stateList->Size(); i++) {
        WriteFile(f, "{");
        for (int j{ 0 }; j < Symtab::nsym - Symtab::ntoken(); j++) {
            Record record = parser->_gotoTable->Find(i, j);
            if (record != nullptr) {
                sprintf(buf, "%d,", record->id);
                WriteFile(f, buf);
            } else {
                WriteFile(f, "MAX_ID,");
            }
        }
        WriteFile(f, "},\n");
    }
    WriteFile(f, "')\n");

    // data right num
    memset(buf, 0, 256);
    WriteFile(f, "define(DATA_RIGHT_NUM, `");

    for (int rId{ 0 }; rId < Rules.size(); rId++) {
        sprintf(buf, "%zd,", Rules[rId]->right.size());
        WriteFile(f, buf);
    }

    WriteFile(f, "')\n");
    // data left id
    memset(buf, 0, 256);
    WriteFile(f, "define(DATA_LEFT_ID, `");
    for (int rId{ 0 }; rId < Rules.size(); rId++) {
        sprintf(buf, "%d,", Rules[rId]->left);
        WriteFile(f, buf);
    }

    WriteFile(f, "')\n");

    // eof token id
    memset(buf, 0, 256);
    sprintf(buf, "define(DATA_EOF_ID, `%d')\n", Symtab::eof->id);
    WriteFile(f, buf);

    // data of return
    memset(buf, 0, 256);
    sprintf(buf, "define(DATA_RETURN, `%s')\n", this->param.c_str());
    WriteFile(f, buf);

    delete[] buf;
}
