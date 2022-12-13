#include "symtab.hpp"
#include "debug.hpp"

static const char* sym_name[3] = { "none", "token", "nterm" };

int Symtab::nsym = 0;

std::map<std::string, Symbol> Symtab::_data;
Symbol Symtab::epsilon = NULL;
Symbol Symtab::eof     = NULL;
Symbol Symtab::start   = NULL;

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
        printf("  %15s -> %3d -> %s\n", it->first.c_str(), it->second->id, sym_name[it->second->clazz]);
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

bool
SymbolListLess(const SymbolList& left, const SymbolList& right) {
    int i{ 0 };

    if ((i = left.size() - right.size()) != 0) {
        return i < 0 ? true : false;
    }

    for (int j{ 0 }; j < left.size(); j++) {
        if ((i = left[j]->id - right[j]->id) != 0) {
            return i < 0 ? true : false;
        }
    }

    return false;
}

bool
SymbolListEqual(const SymbolList& left, const SymbolList& right) {
    if (left.size() != right.size()) {
        return false;
    }

    for (int i{ 0 }; i < left.size(); i++) {
        if (left[i]->id != right[i]->id) {
            return false;
        }
    }

    return true;
}
