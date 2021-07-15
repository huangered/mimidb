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

struct SemaTokenData {
    int id;
    bool sema;
    yih::String name;
    LexToken lexToken;

public:
    SemaTokenData(int _id, bool _sema, yih::String _name) {
        id = _id;
        sema = _sema;
        name = _name;
    }

    SemaTokenData(int _id, bool _sema, LexToken _lexToken) {
        id = _id;
        sema = _sema;
        lexToken = _lexToken;
    }

    int
    Compare(const SemaTokenData* token) {
        int i;
        if ((i = (sema - token->sema)) != 0) {
            return i;
        }

        if (sema) {
            return name.Compare(token->name);
        } else {
            return lexToken->compare(*token->lexToken);
        }
    }
};

typedef SemaTokenData* SemaToken;
typedef std::vector<SemaToken> SemaTokenList;

struct StateItemData {
    int id;
    bool acc;
};

class StateData {
    int _id;
    RuleList _rules;

public:
    StateData(int id) : _id{id} {
    }
    ~StateData();
    RuleList
    GetRules() {
        return _rules;
    }

    void
    ResetRules(RuleList rules) {
        _rules.swap(rules);
    }

    void
    Add(Rule rule) {
        auto cmp = [rule](Rule r) -> bool { return r->Compare(*rule) == 0; };

        auto iter = std::find_if(_rules.begin(), _rules.end(), cmp);

        if (iter == _rules.end()) {
            _rules.push_back(rule);
        }
    }

    void
    Add(std::set<Rule> rules) {
        for (auto iter = rules.begin(); iter != rules.end(); iter++) {
            Add(*iter);
        }
    }

    bool
    MatchRule(RuleList rules1) {
        for (auto rules = rules1.begin(); rules != rules1.end(); rules++) {
            Rule r = *rules;
            auto match = [&](Rule rule) -> bool { return rule->Compare(*r) == 0; };
            auto iter = std::find_if(_rules.begin(), _rules.end(), match);
            if (iter == _rules.end()) {
                return false;
            }
        }
        return true;
    }

    int
    GetId() {
        return _id;
    }
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

    friend std::ostream&
    operator<<(std::ostream& os, const RecordData& dt) {
        if (dt.id == -1) {
            os << "  ";
            return os;
        }
        if (dt.acc) {
            os << "acc";
            return os;
        }
        if (dt.state) {
            os << "s" << dt.id;
        } else {
            os << "r" << dt.id;
        }
        return os;
    }
};

typedef RecordData* Record;

class FirstSet {
private:
    std::vector<SimpleRule> _rules;

    // <sema token id, tok id>
    std::map<int, std::set<Tok>> _firstSet;

public:
    FirstSet(std::vector<SimpleRule> rules) {
        _rules = rules;
        // 更新 _semaTokens;
        for (SimpleRule rule : _rules) {
            SemaToken left = rule->left;
            //_semaTokens[left->id] = left;

            for (SemaToken r : rule->right) {
                //_semaTokens[r->id] = r;
            }
        }
    }

    std::vector<Tok>
    Find(SemaToken nonTerminal) {
        std::set<Tok> r = _firstSet[nonTerminal->id];
        std::vector<Tok> rList;

        rList.insert(rList.end(), r.begin(), r.end());

        return rList;
    }

    std::vector<Tok>
    Find(SemaTokenList tokens, std::vector<Tok> extra) {
        if (tokens.size() == 0) {
            return extra;
        }
        for (SemaToken c : tokens) {
            if (!c->sema) {
                return {c->lexToken->tok};
            }
            return Find(tokens[0]);
        }
        return {};
    }

    void
    Gen() {
        int count;
        do {
            count = 0;

            for (SimpleRule rule : _rules) {
                SemaToken left = rule->left;

                if (_firstSet.count(left->id) == 0) {
                    _firstSet[left->id] = {};
                }

                std::set<Tok> c{};
                if (!rule->right[0]->sema) {
                    c.insert(rule->right[0]->lexToken->tok);
                } else {
                    SemaToken firstRight = rule->right[0];
                    if (_firstSet.count(firstRight->id) > 0) {
                        auto tokens = _firstSet[firstRight->id];
                        c.insert(tokens.begin(), tokens.end());
                    }
                }
                for (Tok cc : c) {
                    if (_firstSet[left->id].count(cc) == 0) {
                        _firstSet[left->id].insert(cc);
                        count++;
                    }
                }
            }

        } while (count > 0);
    }

    void
    print() {
        for (auto entry = _firstSet.begin(); entry != _firstSet.end(); entry++) {
            std::cout << entry->first << " => ";
            for (Tok i : entry->second) {
                std::cout << i << ",";
            }
            std::cout << std::endl;
        }
    }
};

class Parser {
private:
    int _maxState;
    RuleList _rules;
    GotoTable* _gotoTable;
    ActionTable* _actionTable;
    FirstSet* _firstSet;
    StateCollection* _stateList;

    SemaTokenList _terminals;
    SemaTokenList _nonTerminals;

public:
    Parser(std::vector<SimpleRule> rules, SemaTokenList terminals, SemaTokenList nonTerminals);
    ~Parser();
    void GenerateParseTable(void);
    Node Parse(std::vector<LexToken> input);

private:
    void handleState(int i);
    void generateTable(void);
    void expandRules(State state);
    State searchSameState(RuleList newStateRules);

    bool reduce(std::stack<int>& states, std::stack<Node>& syms, Record curRecord);
    bool eatToken(std::stack<int>& states, std::stack<Node>& syms, std::stack<SemaToken>& input, bool* acc);
};

#endif
