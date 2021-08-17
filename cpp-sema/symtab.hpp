#ifndef _symtab_hpp_
#define _symtab_hpp_

#include <string>
#include <map>

enum SymbolClass
{
    unknown,
    token,
    nterm
};

struct Location {
    int line;
    int offset;
};

struct SymbolData {
    int id;
    std::string name;
    Location loc;
    SymbolClass clazz;
};

typedef SymbolData* Symbol;

class Symtab {
private:
    std::map<std::string, Symbol> _data;

public:
    Symtab();
    ~Symtab();

    Symbol SymbolNew(std::string name);
};

#endif