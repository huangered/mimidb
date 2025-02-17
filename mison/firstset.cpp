#include "firstset.hpp"
#include "sema.hpp"
#include "debug.hpp"
#include "symtab.hpp"
#include <map>

FirstSet::FirstSet() {
}

std::vector<int>
FirstSet::find(SymbolList tokens) {
    Symbol t        = tokens[0];
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
FirstSet::Find(const SymbolList& tokens, const std::vector<int>& extra) {
    if (tokens.empty()) {
        return extra;
    }
    Symbol c = tokens[0];
    if (c->clazz == nterm) {
        return find(tokens);
    } else {
        return { c->id };
    }
}

void
FirstSet::Gen() {
    int count;
    do {
        count = 0;

        for (Rule rule : Rules) {
            std::set<int> tokSet;
            int left_id = rule->left->id;

            if (_firstSet.count(left_id) == 0) {
                _firstSet[left_id] = {};
            }

            if (rule->right.empty()) {
                tokSet.insert(Symtab::epsilon->id);
            } else {
                if (rule->right[0]->clazz == token) {
                    tokSet.insert(rule->right[0]->id);
                } else {
                    Symbol firstRight = rule->right[0];
                    if (_firstSet.count(firstRight->id) > 0) {
                        auto tokens = _firstSet[firstRight->id];
                        tokSet.insert(tokens.begin(), tokens.end());
                    }
                }
            }
            for (int tok : tokSet) {
                if (_firstSet[left_id].count(tok) == 0) {
                    _firstSet[left_id].insert(tok);
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
        printf(" (%10s) (%3d) => ", Symtab::GetName(entry->first).c_str(), entry->first);
        for (int i : entry->second) {
            printf("(%10s) (%3d), ",Symtab::GetName(i).c_str(), i);
        }
        printf("\n");
    }
#endif
}
