#include "sema/sema.hpp"
#include <algorithm>

StateData::StateData(int id)
    : _id{ id } {
}

StateData::~StateData() {
    for (Rule rule : _rules) {
        delete rule;
    }
}

RuleList
StateData::GetRules() {
    return _rules;
}

void
StateData::ResetRules(RuleList& rules) {
    _rules.swap(rules);
}

void
StateData::Add(Rule rule) {
    auto cmp = [rule](Rule r) -> bool { return *r == *rule; };

    auto iter = std::find_if(_rules.begin(), _rules.end(), cmp);

    if (iter == _rules.end()) {
        _rules.push_back(rule);
    }
}

void
StateData::Add(std::set<Rule> rules) {
    for (auto iter = rules.begin(); iter != rules.end(); iter++) {
        Add(*iter);
    }
}

bool
StateData::MatchRule(const RuleList& rules1) {
    for (auto rules = rules1.begin(); rules != rules1.end(); rules++) {
        Rule r     = *rules;
        auto match = [&](Rule rule) -> bool { return *rule == *r; };
        auto iter  = std::find_if(_rules.begin(), _rules.end(), match);
        if (iter == _rules.end()) {
            return false;
        }
    }
    return true;
}

int
StateData::GetId() {
    return _id;
}