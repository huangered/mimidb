#ifndef _rule_hpp_
#define _rule_hpp_

#include "node.hpp"
#include <vector>
#include <set>

class SemaTokenData;
typedef SemaTokenData* SemaToken;
typedef std::vector<SemaToken> SemaTokenList;

class RuleData {
public:
    int lineId;
    int id;
    SemaToken left;
    SemaTokenList right;
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

    SemaToken left;
    SemaTokenList right;
    // look ahead 检查
    std::vector<int> tokens;

    std::string func_block;

public:
    bool IsDotEnd();

    SemaToken GetTokenAfterDot();

    SemaTokenList GetStringAfterDot();

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
