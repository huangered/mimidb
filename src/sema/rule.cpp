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
    SemaTokenList tokens;
    for (int i{ dot + 1 }; i != right.size(); i++) {
        tokens.push_back(right[i]);
    }
    return tokens;
}

void
RuleData::SetToken(Tok token) {
    tokens.push_back(token);
    auto j = [](Tok l, Tok r) -> bool { return l < r; };
    std::sort(tokens.begin(), tokens.end(), j);
}

void
RuleData::AppendTokens(TokList tokenList) {
    tokens.insert(tokens.end(), tokenList.begin(), tokenList.end());

    auto j = [](Tok l, Tok r) -> bool { return l < r; };
    std::sort(tokens.begin(), tokens.end(), j);
}

TokList
RuleData::GetTokens() {
    return tokens;
}

void
RuleData::SetTokens(TokList tokenList) {
    tokens.swap(tokenList);
    auto j = [](Tok l, Tok r) -> bool { return l < r; };
    std::sort(tokens.begin(), tokens.end(), j);
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

int
RuleData::Compare(RuleData& other) {
    int i;
    if ((i = left->Compare(*other.left)) != 0) {
        return i;
    }

    if ((i = (right.size() - other.right.size())) != 0) {
        return i;
    }

    for (int j = 0; j < right.size(); j++) {
        if ((i = right[j]->Compare(*other.right[j])) != 0) {
            return i;
        }
    }

    if ((i = (tokens.size() - other.tokens.size())) != 0) {
        return i;
    }

    for (int j = 0; j < tokens.size(); j++) {
        if ((i = tokens[j] - other.tokens[j]) != 0) {
            return i;
        }
    }

    return dot - other.dot;
}

Node
RuleData::Format(SemaToken token, std::vector<Node> children) {
    Node n = new NodeData{};
    n->AddAll(children);
    return n;
}