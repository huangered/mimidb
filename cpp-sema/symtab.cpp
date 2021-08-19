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
#ifdef _log_	
	printf("symbol new %s => %d\n", name.c_str(), symbol->id);
#endif	
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
    
    printf("nterm tag %d, num(%d)\n", SymbolClass::nterm, nnterm());
    printf("token tag %d, num(%d)\n", SymbolClass::token, ntoken());
    for (auto it = _data.begin(); it != _data.end(); it++) {
        // How do I access each element?
        printf("  %s -> %d -> %d\n", it->first.c_str(), it->second->id, it->second->clazz);
    }
#endif
}

int Symtab::nnterm(){
  int i=0;
      for (auto it = _data.begin(); it != _data.end(); it++) {
	if(it->second->clazz == nterm) {
	  i++;
	}
      }
  return i;
}

int Symtab::ntoken(){
  int i=0;
      for (auto it = _data.begin(); it != _data.end(); it++) {
	if(it->second->clazz == token) {
          i++;
	}
      }
  return i;
}

