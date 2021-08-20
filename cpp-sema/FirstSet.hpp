#ifndef _firstset_hpp_
#define _firstset_hpp_

#include "rule.hpp"

class FirstSet {
private:
    std::vector<SimpleRule> _rules;

    // <sema token id, tok id>
    std::map<int, std::set<int>> _firstSet;

public:
    FirstSet(const std::vector<SimpleRule>& rules);

    TokList Find(const SemaTokenList& tokens, const TokList& extra);

    void Gen();

    void Print();

private:
    TokList find(SemaTokenList tokens);
};

#endif