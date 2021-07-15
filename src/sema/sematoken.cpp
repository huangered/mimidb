#include "sema/sema.hpp"

SemaTokenData::SemaTokenData(int _id, bool _sema, yih::String _name) {
    id       = _id;
    sema     = _sema;
    name     = _name;
    lexToken = nullptr;
}

SemaTokenData::SemaTokenData(int _id, bool _sema, LexToken _lexToken) {
    id       = _id;
    sema     = _sema;
    lexToken = _lexToken;
}

SemaTokenData::~SemaTokenData() {
}

int
SemaTokenData::Compare(const SemaTokenData* token) {
    int i;
    if ((i = (sema - token->sema)) != 0) {
        return i;
    }

    if (sema) {
        return id - token->id;
    } else {
        return lexToken->compare(*token->lexToken);
    }
}

// ===

StateData::StateData(int id) : _id{id} {
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
StateData::ResetRules(RuleList rules) {
    _rules.swap(rules);
}

void
StateData::Add(Rule rule) {
    auto cmp = [rule](Rule r) -> bool { return r->Compare(*rule) == 0; };

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
StateData::MatchRule(RuleList rules1) {
    for (auto rules = rules1.begin(); rules != rules1.end(); rules++) {
        Rule r     = *rules;
        auto match = [&](Rule rule) -> bool { return rule->Compare(*r) == 0; };
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