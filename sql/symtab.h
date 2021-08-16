#ifndef _sema_h_
#define _sema_h_

#include "c_util/chash.h"

extern hash_table* symbol_tbl;

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

void symbols_new(void);

#endif // !_sema_h_
