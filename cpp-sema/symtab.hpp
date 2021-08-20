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
public:
    static std::map<std::string, Symbol> _data;

public:
    static int nsym;
    static int nnterm();
    static int ntoken();

public:
    Symtab();
    ~Symtab();
    static void Init();
    static Symbol SymbolNew(std::string name);
    static int GetId(std::string name);
    static std::string GetName(int id);
    static void Print(void);
};

#endif
