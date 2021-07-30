#ifndef _rule_hpp_
#define _rule_hpp_

#include "lex/lexer.hpp"
#include "sema/node.hpp"
#include <vector>
#include <set>

class SemaTokenData;
typedef SemaTokenData* SemaToken;
typedef std::vector<SemaToken> SemaTokenList;

class SimpleRuleData {
public:
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
    int cur_state;
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

    void SetToken(Tok token);

    void AppendTokens(TokList tokens);

    RuleData* Clone();

    TokList GetTokens();

    void SetTokens(TokList tokens);

    // 用户自定义的规则
    Node Format(const SemaToken token, const std::vector<Node>& children);

    bool operator==(const RuleData& other);
};

typedef RuleData* Rule;
typedef std::vector<Rule> RuleList;

#endif // !_rule_hpp_
