#include "FirstSet.hpp"
#include "sema.hpp"
#include "debug.hpp"
#include "symtab.hpp"

FirstSet::FirstSet(const RuleList& rules)
    : _rules{ rules } {
}

std::vector<int>
FirstSet::find(SemaTokenList tokens) {
    SemaToken t     = tokens[0];
    std::set<int> r = _firstSet[t->id];

    if (r.empty()) {
        return {};
    }

    if (r.count(Symtab::epsilon->id) > 0) {
        tokens.erase(tokens.begin());
        std::vector<int> q = Find(tokens, {});
        r.insert(q.begin(), q.end());
    }

    r.erase(Symtab::epsilon->id);

    return { r.begin(), r.end() };
}

std::vector<int>
FirstSet::Find(const SemaTokenList& tokens, const std::vector<int>& extra) {
    if (tokens.empty()) {
        return extra;
    }
    SemaToken c = tokens[0];
    if (c->sema) {
        return find(tokens);
    } else {
        return { Symtab::GetId(c->name) };
    }
}

void
FirstSet::Gen() {
    int count;
    do {
        count = 0;

        for (Rule rule : _rules) {
            std::set<int> tokSet;
            SemaToken left = rule->left;

            if (_firstSet.count(left->id) == 0) {
                _firstSet[left->id] = {};
            }

            if (rule->right.empty()) {
                tokSet.insert(Symtab::epsilon->id);
            } else {
                if (!rule->right[0]->sema) {
                    tokSet.insert(Symtab::GetId(rule->right[0]->name));
                } else {
                    SemaToken firstRight = rule->right[0];
                    if (_firstSet.count(firstRight->id) > 0) {
                        auto tokens = _firstSet[firstRight->id];
                        tokSet.insert(tokens.begin(), tokens.end());
                    }
                }
            }
            for (int tok : tokSet) {
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
        for (int i : entry->second) {
            printf("%d,", i);
        }
        printf("\n");
    }
#endif
}
