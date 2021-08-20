#include "state.hpp"
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


StateCollection::~StateCollection() {
    for (State state : stateList) {
        delete state;
    }
}

int
StateCollection::Size() {
    return stateList.size();
}

bool
StateCollection::IsEmpty(int stateId) {
    return stateList[stateId]->GetRules().size() == 0;
}

void
StateCollection::Add(State state) {
    stateList.push_back(state);
}

void
StateCollection::Add(int stateId, Rule rule) {
    stateList[stateId]->Add(rule);
}

RuleList
StateCollection::GetRules(int stateId) {
    return stateList[stateId]->GetRules();
}

State
StateCollection::GetState(int stateId) {
    return stateList[stateId];
}