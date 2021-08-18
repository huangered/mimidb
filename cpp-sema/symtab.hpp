#ifndef _symtab_hpp_
#define _symtab_hpp_

#include <string>
#include <map>

enum SymbolClass
{
    none,
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
    static std::map<std::string, Symbol> _data;
    static int nsym;

public:
    Symtab();
    ~Symtab();

    static Symbol SymbolNew(std::string name);
    static Symbol SymbolGet(std::string name);
};

#endif