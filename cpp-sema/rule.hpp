#ifndef _rule_hpp_
#define _rule_hpp_

#include "c.tab.hpp"
#include "node.hpp"
#include <vector>
#include <set>

class SemaTokenData;
typedef SemaTokenData* SemaToken;
typedef std::vector<SemaToken> SemaTokenList;

class SimpleRuleData {
public:
    int lineId;
    int id;
    SemaToken left;
    SemaTokenList right;
    std::string funcBlock;
};

typedef SimpleRuleData* SimpleRule;

SimpleRule make_rule(int id, SemaToken left, SemaTokenList right, std::string block);

class RuleData {
public:
    int id;
    int dot;
    int next_state;
    bool root;

    SemaToken left;
    SemaTokenList right;
    // look ahead 检查
    TokList tokens;

    std::string func_block;

public:
    bool IsDotEnd();

    SemaToken GetTokenAfterDot();

    SemaTokenList GetStringAfterDot();

    void SetToken(int token);

    void AppendTokens(TokList tokens);

    RuleData* Clone();

    TokList GetTokens();

    void SetTokens(TokList tokens);

     bool operator==(const RuleData& other);
};

typedef RuleData* Rule;
typedef std::vector<Rule> RuleList;

#endif // !_rule_hpp_
