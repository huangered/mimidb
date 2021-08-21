#include "symtab.hpp"
#include "debug.hpp"

int Symtab::nsym = 0;

std::map<std::string, Symbol> Symtab::_data;
Symbol Symtab::epsilon = nullptr;
Symbol Symtab::eof     = nullptr;

Symtab::Symtab() {
}

Symtab::~Symtab() {
}

void
Symtab::Init() {
    // 系统内部保留符号
    epsilon        = SymbolNew("$t_epsilon");
    epsilon->clazz = token;
    eof            = SymbolNew("$t_eof");
    eof->clazz     = token;
}

Symbol
Symtab::SymbolNew(std::string name) {
    if (_data.count(name) == 0) {
        Symbol symbol = new SymbolData{};
        symbol->name  = name;
        symbol->clazz = none;
        symbol->id    = nsym++;
        _data[name]   = symbol;
#ifdef _log_
        printf("symbol new %15s => %d\n", name.c_str(), symbol->id);
#endif
    }

    return _data[name];
}

int
Symtab::GetId(std::string name) {
    return _data[name]->id;
}

std::string
Symtab::GetName(int id) {
    for (auto it = _data.begin(); it != _data.end(); it++) {
        if (it->second->id == id) {
            return it->first;
        }
    }
    return "";
}

void
Symtab::Print() {
#ifdef _log_
    printf("Symtab: %d\n", nsym);

    printf("nterm tag %d, num(%d)\n", SymbolClass::nterm, nnterm());
    printf("token tag %d, num(%d)\n", SymbolClass::token, ntoken());
    for (auto it = _data.begin(); it != _data.end(); it++) {
        // How do I access each element?
        printf("  %15s -> %3d -> %3d\n", it->first.c_str(), it->second->id, it->second->clazz);
    }
#endif
}

int
Symtab::nnterm() {
    int i = 0;
    for (auto it = _data.begin(); it != _data.end(); it++) {
        if (it->second->clazz == nterm) {
            i++;
        }
    }
    return i;
}

int
Symtab::ntoken() {
    int i = 0;
    for (auto it = _data.begin(); it != _data.end(); it++) {
        if (it->second->clazz == token) {
            i++;
        }
    }
    return i;
}
