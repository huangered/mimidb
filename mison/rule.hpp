#ifndef _rule_hpp_
#define _rule_hpp_

#include <vector>
#include <set>
#include "symtab.hpp"

class RuleData {
public:
    bool root;
    int lineId;
    int id;
    Symbol left;
    SymbolList right;
    std::string funcBlock;

public:
    void print();
};

typedef RuleData* Rule;

typedef std::vector<Rule> RuleList;

extern RuleList Rules;

class ItemData {
public:
    // rule id
    int id;
    int dot;
    int next_state;

    // look ahead 检查
    std::vector<int> tokens;

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

#define ItemLeft(item)      (Rules[item->id]->left)
#define ItemRoot(item)      (Rules[item->id]->root)
#define ItemRight(item, i)  (Rules[item->id]->right[(i)])
#define ItemRights(item)    (Rules[item->id]->right)
#define ItemRightSize(item) (Rules[item->id]->right.size())

#endif // !_rule_hpp_
