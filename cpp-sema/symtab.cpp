#include "symtab.hpp"

Symtab::Symtab() {
}

Symtab::~Symtab() {
}

Symbol
Symtab::SymbolNew(std::string name) {
    Symbol symbol = new SymbolData{};
    symbol->name  = name;
    symbol->clazz = unknown;

    _data[name] = symbol;

    return symbol;
}