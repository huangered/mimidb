#include "sema/sema.hpp"

FirstSet::FirstSet(std::vector<SimpleRule> rules) {
    _rules = rules;
}

TokList
FirstSet::Find(SemaToken nonTerminal) {
    std::set<Tok> r = _firstSet[nonTerminal->id];
    std::vector<Tok> rList;

    rList.insert(rList.end(), r.begin(), r.end());

    return rList;
}

TokList
FirstSet::Find(SemaTokenList tokens, std::vector<Tok> extra) {
    if (tokens.size() == 0) {
        return extra;
    }
    for (SemaToken c : tokens) {
        if (!c->sema) {
            return {c->lexToken->tok};
        }
        return Find(tokens[0]);
    }
    return {};
}

void
FirstSet::Gen() {
    int count;
    do {
        count = 0;

        for (SimpleRule rule : _rules) {
            std::set<Tok> tokSet;
            SemaToken left = rule->left;

            if (_firstSet.count(left->id) == 0) {
                _firstSet[left->id] = {};
            }


            if (!rule->right[0]->sema) {
                tokSet.insert(rule->right[0]->lexToken->tok);
            } else {
                SemaToken firstRight = rule->right[0];
                if (_firstSet.count(firstRight->id) > 0) {
                    auto tokens = _firstSet[firstRight->id];
                    tokSet.insert(tokens.begin(), tokens.end());
                }
            }
            for (Tok tok : tokSet) {
                if (_firstSet[left->id].count(tok) == 0) {
                    _firstSet[left->id].insert(tok);
                    count++;
                }
            }
        }

    } while (count > 0);
}

void
FirstSet::Print() {
    for (auto entry = _firstSet.begin(); entry != _firstSet.end(); entry++) {
        std::cout << entry->first << " => ";
        for (Tok i : entry->second) {
            std::cout << i << ",";
        }
        std::cout << std::endl;
    }
}