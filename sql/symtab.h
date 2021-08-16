#ifndef _sema_h_
#define _sema_h_

#include "hash.h"

typedef int SymbolNumber;

enum SymbolClass
{
    token, // 终止符
    nterm  // 非终止符
};

typedef struct symbol {
    char* name;
    SymbolNumber number;

    enum SymbolClass clazz;
} Symbol;

Symbol* symbol_new(const char* name);
Symbol* symbol_from_uniqstr(const char* name);

hash_table* symbols_new();

#endif // !_sema_h_
