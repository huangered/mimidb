﻿#ifndef _sema_hpp_
#define _sema_hpp_

#include "lexer.hpp"
#include "FindAll.hpp"
#include "node.hpp"
#include "rule.hpp"
#include "table.hpp"
#include "FirstSet.hpp"
#include "state.hpp"

#include <map>
#include <set>
#include <stack>
#include <string>
#include <iostream>
#include <memory>

// bool SemaTokenListEqual(const SemaTokenList& left, const SemaTokenList& right);

struct group_key {
    int dot;
    Symbol left;
    SymbolList right;

    bool operator<(const group_key& other) const;
};

class RecordData {
public:
    bool acc;
    bool state;
    int id;
};

typedef RecordData* Record;

class Parser {
private:
    int _maxState;
    std::map<std::string, std::string> _typeMap;
    std::vector<Rule> _originRules;
    ItemList _rules;
    std::unique_ptr<GotoTable> _gotoTable;
    std::unique_ptr<ActionTable> _actionTable;
    std::unique_ptr<FirstSet> _firstSet;
    std::unique_ptr<StateCollection> _stateList;

public:
    Parser(const std::vector<Rule>& rules);
    ~Parser();
    void SetTypeMap(const std::map<std::string, std::string>& _typeMap);
    void GenerateParseTable(void);

private:
    void handleState(int stateId);
    void generateTable(void);
    void expandRules(State state);
    State searchSameState(const ItemList& newStateRules);

    // code generate
    std::string funcReplace(const Item rule);

    friend class Output;
};

#endif
