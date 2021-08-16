#include "symtab.h"
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "global.h"

hash_table* symbol_tbl;

static int sym_hash(void* sym);
static bool sym_equal(void* l, void* r);

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


void
symbols_new(void) {
  symbol_tbl = hash_init(8, sym_hash, sym_equal);
    Symbol* accept = symbol_new("$accept");
    Symbol* end = symbol_new("$end");
    
}

int
sym_hash(void* sym){
  return 0;
}

bool
sym_equal(void* l, void* r){
  return false;
}
