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
    //auto j = [](Tok l, Tok r) -> bool { return l < r; };
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

    if (right.size() != other.right.size()) {
        return false;
    }

    for (int j = 0; j < right.size(); j++) {
        if (right[j]->id != other.right[j]->id) {
            return false;
        }
    }

    if (tokens != other.tokens) {
        return false;
    }

    return dot == other.dot;
}

Node
RuleData::Format(SemaToken token, std::vector<Node> children) {
    Node n = new NodeData{};
    n->AddAll(children);
    return n;
}