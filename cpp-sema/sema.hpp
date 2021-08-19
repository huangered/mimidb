#ifndef _sema_hpp_
#define _sema_hpp_

#include "lexer.hpp"
#include "FindAll.hpp"
#include "node.hpp"
#include "rule.hpp"
#include "table.hpp"
#include "FirstSet.hpp"

#include <map>
#include <set>
#include <stack>
#include <string>
#include <iostream>
#include <memory>

class SemaTokenData {
public:
    int id;
    bool sema;
    std::string name;
};

typedef SemaTokenData* SemaToken;
typedef std::vector<SemaToken> SemaTokenList;

bool SemaTokenListEqual(const SemaTokenList& left, const SemaTokenList& right);

struct group_key {
    int dot;
    SemaToken left;
    SemaTokenList right;

    bool operator<(const group_key& other) const;
};

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

class RecordData {
public:
    bool acc;
    bool state;
    int id;
};

std::ostream& operator<<(std::ostream& os, const RecordData& dt);

typedef RecordData* Record;

class Parser {
private:
    int _maxState;
    std::map<std::string, std::string> _typeMap;
    std::vector<SimpleRule> _originRules;
    RuleList _rules;
    std::unique_ptr<GotoTable> _gotoTable;
    std::unique_ptr<ActionTable> _actionTable;
    std::unique_ptr<FirstSet> _firstSet;
    std::unique_ptr<StateCollection> _stateList;

public:
    Parser(const std::vector<SimpleRule>& rules);
    ~Parser();
    void SetTypeMap(const std::map<std::string, std::string>& _typeMap);
    void GenerateParseTable(void);
    std::pair<bool, Node> Parse(const std::vector<LexToken>& input);

private:
    void handleState(int stateId);
    void generateTable(void);
    void expandRules(State state);
    State searchSameState(const RuleList& newStateRules);

    bool reduce(std::stack<int>& states, std::stack<Node>& syms, const Record curRecord);
    bool eatToken(std::stack<int>& states, std::stack<Node>& syms, std::stack<LexToken>& input, bool* acc);

    // code generate
    std::string funcReplace(const Rule rule);

    friend class Output;
};

#endif
