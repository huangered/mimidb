#ifndef _state_hpp_
#define _state_hpp_

#include "rule.hpp"

class StateData {
    int _id;
    RuleList _rules;

public:
    StateData(int id);
    ~StateData();

    RuleList GetRules();

    void ResetRules(RuleList& rules);

    void Add(Rule rule);

    void Add(std::set<Rule> rules);

    bool MatchRule(const RuleList& rules);

    int GetId();
};

typedef StateData* State;
typedef std::vector<State> StateList;

class StateCollection {
    StateList stateList;

public:
    ~StateCollection();
    int Size();
    bool IsEmpty(int stateId);
    void Add(State state);
    void Add(int stateId, Rule rule);
    RuleList GetRules(int stateId);
    State GetState(int stateId);
};

#endif // !_state_hpp_
