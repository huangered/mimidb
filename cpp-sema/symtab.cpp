#include "symtab.hpp"
#include "debug.hpp"

int Symtab::nsym = 0;

std::map<std::string, Symbol> Symtab::_data;

Symtab::Symtab() {
}

Symtab::~Symtab() {
}

void
Symtab::Init() {
    Symbol symbol = SymbolNew("$t_epsilon");
    symbol->clazz = token;
}

Symbol
Symtab::SymbolNew(std::string name) {
    if (_data.count(name) == 0) {
        Symbol symbol = new SymbolData{};
        symbol->name  = name;
        symbol->clazz = none;
        symbol->id    = nsym++;
        _data[name]   = symbol;
    }

    return _data[name];
}

Symbol
Symtab::SymbolGet(std::string name) {
    if (_data.count(name) == 0) {
        return nullptr;
    }
    return _data[name];
}

void
Symtab::Print() {
#ifdef _log_
    printf("Symtab: %d\n", nsym);
    printf("nterm %d\n", SymbolClass::nterm);
    printf("token %d\n", SymbolClass::token);
    for (auto it = _data.begin(); it != _data.end(); it++) {
        // How do I access each element?
        printf("  %s -> %d -> %d\n", it->first.c_str(), it->second->id, it->second->clazz);
    }
#endif
}