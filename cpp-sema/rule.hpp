#ifndef _rule_hpp_
#define _rule_hpp_

#include <vector>
#include <set>
#include <string>
#include "symtab.hpp"

class RuleData {
public:
    int lineId;
    int id;
    int left;
    SymbolList right;
    std::string funcBlock;
};

typedef RuleData* Rule;

typedef std::vector<Rule> RuleList;

class ItemData {
public:
    int id;
    int dot;
    int next_state;
    bool root;

    int left;
    SymbolList right;
    // look ahead 检查
    std::vector<int> tokens;

    std::string func_block;

public:
    bool IsDotEnd();

    Symbol GetTokenAfterDot();

    SymbolList GetStringAfterDot();

    void SetToken(int token);

    void AppendTokens(std::vector<int> tokens);

    ItemData* Clone();

    std::vector<int> GetTokens();

    void SetTokens(std::vector<int> tokens);

    bool operator==(const ItemData& other);
};

typedef ItemData* Item;
typedef std::vector<Item> ItemList;

#endif // !_rule_hpp_
