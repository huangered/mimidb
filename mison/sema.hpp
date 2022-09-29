#ifndef _sema_hpp_
#define _sema_hpp_

#include "lexer.hpp"
#include "findall.hpp"
#include "node.hpp"
#include "rule.hpp"
#include "table.hpp"
#include "firstset.hpp"
#include "state.hpp"

#include <map>
#include <set>
#include <stack>
#include <string>
#include <memory>

class RecordData {
public:
    bool acc;
    bool state;
    int id;
};

typedef RecordData* Record;

class SemaParser {
private:
    int _maxState;
    std::map<std::string, std::string> _typeMap;

    std::unique_ptr<GotoTable> _gotoTable;
    std::unique_ptr<ActionTable> _actionTable;
    std::unique_ptr<FirstSet> _firstSet;
    std::unique_ptr<StateCollection> _stateList;

public:
    SemaParser(const std::map<std::string, std::string>& _typeMap);
    SemaParser(const SemaParser&)            = delete;
    SemaParser& operator=(const SemaParser&) = delete;
    ~SemaParser();
    void GenerateParseTable(void);

private:
    void handleState(int stateId);
    void generateTable(void);
    void expandRules(State state);
    State searchSameState(const ItemList& newStateRules);

    // code generate
    std::string funcReplace(const Rule rule);

    friend class Output;
};

#endif
