#include "symtab.hpp"

int Symtab::nsym = 0;
std::map<std::string, Symbol> Symtab::_data;

Symtab::Symtab()
{
}

Symtab::~Symtab() {
}

Symbol
Symtab::SymbolNew(std::string name) {
    if (_data.count(name) == 0) {
        Symbol symbol = new SymbolData{};
        symbol->name  = name;
        symbol->clazz = none;
        symbol->id    = nsym++;
        _data[name] = symbol;
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