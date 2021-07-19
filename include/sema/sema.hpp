#ifndef _sema_hpp_
#define _sema_hpp_

#include "lex/lexer.hpp"
#include "util/generic.hpp"
#include "sema/node.hpp"
#include "sema/rule.hpp"
#include "sema/table.hpp"
#include "util/generic.hpp"

#include <map>
#include <set>
#include <stack>
#include <string>
#include <iostream>

struct SemaTokenData1 {
    int id;
    std::string name;
};

class TokenData {
    public:
        virtual int GetId();
};

struct SemaTokenData {
    int id;
    bool sema;
    std::string name;
    LexToken lexToken;

public:
    SemaTokenData(int _id, bool _sema, std::string _name);

    SemaTokenData(int _id, bool _sema, LexToken _lexToken);

    ~SemaTokenData();

    int Compare(const SemaTokenData* token);
};

typedef SemaTokenData* SemaToken;
typedef std::vector<SemaToken> SemaTokenList;

class StateData {
    int _id;
    RuleList _rules;

public:
    StateData(int id);
    ~StateData();

    RuleList GetRules();

    void ResetRules(RuleList rules);

    void Add(Rule rule);

    void Add(std::set<Rule> rules);

    bool MatchRule(RuleList rules1);

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

struct RecordData {
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
    FirstSet(std::vector<SimpleRule> rules);

    TokList Find(SemaToken nonTerminal);

    TokList Find(SemaTokenList tokens, TokList extra);

    void Gen();

    void Print();
};

class Parser {
private:
    int _maxState;
    RuleList _rules;
    GotoTable* _gotoTable;
    ActionTable* _actionTable;
    FirstSet* _firstSet;
    StateCollection* _stateList;

public:
    Parser(std::vector<SimpleRule> rules);
    ~Parser();
    void GenerateParseTable(void);
    Node Parse(std::vector<LexToken> input);

private:
    void handleState(int i);
    void generateTable(void);
    void expandRules(State state);
    State searchSameState(RuleList newStateRules);

    bool reduce(std::stack<int>& states, std::stack<Node>& syms, Record curRecord);
    bool eatToken(std::stack<int>& states, std::stack<Node>& syms, std::stack<LexToken>& input, bool* acc);
};

#endif
