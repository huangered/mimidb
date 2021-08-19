﻿#include "sema.hpp"
#include "debug.hpp"

FirstSet::FirstSet(const std::vector<SimpleRule>& rules)
    : _rules{ rules } {
}

TokList
FirstSet::find(SemaTokenList tokens) {
    SemaToken t     = tokens[0];
    std::set<Tok> r = _firstSet[t->id];

    if (r.empty()) {
        return {};
    }

    if (r.count(Tok::epsilon) > 0) {
        tokens.erase(tokens.begin());
        TokList q = Find(tokens, {});
        r.insert(q.begin(), q.end());
    }

    r.erase(Tok::epsilon);

    return { r.begin(), r.end() };
}

TokList
FirstSet::Find(const SemaTokenList& tokens, const TokList& extra) {
    if (tokens.empty()) {
        return extra;
    }
    SemaToken c = tokens[0];
    if (c->sema) {
        return find(tokens);
    } else {
        return { GetTokByName(c->name) };
    }
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

            if (rule->right.empty()) {
                tokSet.insert(Tok::epsilon);
            } else {
                if (!rule->right[0]->sema) {
                    tokSet.insert(GetTokByName(rule->right[0]->name));
                } else {
                    SemaToken firstRight = rule->right[0];
                    if (_firstSet.count(firstRight->id) > 0) {
                        auto tokens = _firstSet[firstRight->id];
                        tokSet.insert(tokens.begin(), tokens.end());
                    }
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
#ifdef _log_
    printf("\nfirset: \n");
    for (auto entry = _firstSet.begin(); entry != _firstSet.end(); entry++) {
        printf("  %d =>", entry->first);
        for (Tok i : entry->second) {
            printf("%d,", i);
        }
        printf("\n");
    }
#endif
}