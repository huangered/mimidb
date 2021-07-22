#include "sema/rule.hpp"
#include "sema/sema.hpp"

SimpleRule
make_rule(int id, SemaToken left, SemaTokenList right) {
    SimpleRule rule = new SimpleRuleData{ id, left, right };
    return rule;
}

bool
RuleData::IsDotEnd() {
    return dot == right.size();
}

SemaToken
RuleData::GetTokenAfterDot() {
    return right[dot];
}

SemaTokenList
RuleData::GetStringAfterDot() {
    SemaTokenList t{ right.begin() + dot + 1, right.end() };
    return t;
}

void
RuleData::SetToken(Tok token) {
    tokens.push_back(token);
    std::sort(tokens.begin(), tokens.end(), std::less<Tok>());
}

void
RuleData::AppendTokens(TokList tokenList) {
    tokens.insert(tokens.end(), tokenList.begin(), tokenList.end());
    std::sort(tokens.begin(), tokens.end(), std::less<Tok>());
}

TokList
RuleData::GetTokens() {
    return tokens;
}

void
RuleData::SetTokens(TokList tokenList) {
    tokens.swap(tokenList);
    std::sort(tokens.begin(), tokens.end(), std::less<Tok>());
}

RuleData*
RuleData::Clone() {
    RuleData* rule   = new RuleData{};
    rule->id         = id;
    rule->left       = left;
    rule->right      = right;
    rule->dot        = dot;
    rule->cur_state  = cur_state;
    rule->next_state = next_state;
    rule->root       = root;
    rule->tokens     = tokens;
    return rule;
}

bool
RuleData::operator==(const RuleData& other) {
    if (left->id != other.left->id) {
        return false;
    }

    if (!SemaTokenListEqual(right, other.right)) {
        return false;
    }

    if (tokens != other.tokens) {
        return false;
    }

    return dot == other.dot;
}

Node
RuleData::Format(const SemaToken token, const std::vector<Node>& children) {
    Node n = new NodeData{ token->name };

    n->AddAll(children);
    return n;
}