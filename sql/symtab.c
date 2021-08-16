#include "symtab.h"
#include <stdlib.h>
#include <assert.h>
#include "global.h"


Symbol*
symbol_new(const char* name) {
    Symbol* res = malloc(sizeof *res);
    assert(res);
    res->name   = name;
    res->number = Params.nsyms;

    Params.nsyms++;

    return res;
}
Symbol*
symbol_from_uniqstr(const char* name) {
    return symbol_new(name);
}


hash_table*
symbols_new() {
    Symbol* accept = symbol_new("accept");
    return NULL;
}