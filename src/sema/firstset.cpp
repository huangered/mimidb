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
            SemaToken left = rule->left;

            if (_firstSet.count(left->id) == 0) {
                _firstSet[left->id] = {};
            }

            std::set<Tok> c{};
            if (!rule->right[0]->sema) {
                c.insert(rule->right[0]->lexToken->tok);
            } else {
                SemaToken firstRight = rule->right[0];
                if (_firstSet.count(firstRight->id) > 0) {
                    auto tokens = _firstSet[firstRight->id];
                    c.insert(tokens.begin(), tokens.end());
                }
            }
            for (Tok cc : c) {
                if (_firstSet[left->id].count(cc) == 0) {
                    _firstSet[left->id].insert(cc);
                    count++;
                }
            }
        }

    } while (count > 0);
}

void
FirstSet::print() {
    for (auto entry = _firstSet.begin(); entry != _firstSet.end(); entry++) {
        std::cout << entry->first << " => ";
        for (Tok i : entry->second) {
            std::cout << i << ",";
        }
        std::cout << std::endl;
    }
}