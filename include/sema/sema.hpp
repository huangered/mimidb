#ifndef _sema_hpp_
#define _sema_hpp_

#include "lex/lexer.hpp"
#include "sema/FindAll.hpp"
#include "sema/node.hpp"
#include "sema/rule.hpp"
#include "sema/table.hpp"

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

class FirstSet {
private:
    std::vector<SimpleRule> _rules;

    // <sema token id, tok id>
    std::map<int, std::set<Tok>> _firstSet;

public:
    FirstSet(const std::vector<SimpleRule>& rules);

    TokList Find(const SemaTokenList& tokens, const TokList& extra);

    void Gen();

    void Print();

private:
    TokList find(SemaTokenList tokens);
};

class Parser {
private:
    int _maxState;
    std::vector<SimpleRule> _originRules;
    RuleList _rules;
    std::unique_ptr<GotoTable> _gotoTable;
    std::unique_ptr<ActionTable> _actionTable;
    std::unique_ptr<FirstSet> _firstSet;
    std::unique_ptr<StateCollection> _stateList;

public:
    Parser(const std::vector<SimpleRule>& rules);
    ~Parser();
    void GenerateParseTable(void);
    std::pair<bool, Node> Parse(const std::vector<LexToken>& input);

    // 生成 cpp 代码
    void GenerateCppCode(const char* path);

private:
    void handleState(int stateId);
    void generateTable(void);
    void expandRules(State state);
    State searchSameState(const RuleList& newStateRules);

    bool reduce(std::stack<int>& states, std::stack<Node>& syms, const Record curRecord);
    bool eatToken(std::stack<int>& states, std::stack<Node>& syms, std::stack<LexToken>& input, bool* acc);
};

#endif
