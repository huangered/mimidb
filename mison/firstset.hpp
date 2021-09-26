#ifndef _firstset_hpp_
#define _firstset_hpp_

#include "rule.hpp"
#include "symtab.hpp"
#include <map>

class FirstSet {
private:
    // <sema token id, tok id>
    std::map<int, std::set<int>> _firstSet;

public:
    FirstSet();

    std::vector<int> Find(const SymbolList& tokens, const std::vector<int>& extra);

    void Gen();

    void Print();

private:
    std::vector<int> find(SymbolList tokens);
};

#endif
