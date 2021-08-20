#include "rule.hpp"
#include "sema.hpp"

Rule
make_rule(int id, SemaToken left, SemaTokenList right, std::string block) {
    Rule rule = new RuleData{ 0, id, left, right , block};
    return rule;
}

bool
ItemData::IsDotEnd() {
    return dot == right.size();
}

SemaToken
ItemData::GetTokenAfterDot() {
    return right[dot];
}

SemaTokenList
ItemData::GetStringAfterDot() {
    SemaTokenList t{ right.begin() + dot + 1, right.end() };
    return t;
}

void
ItemData::SetToken(int token) {
    tokens.push_back(token);
    std::sort(tokens.begin(), tokens.end(), std::less<int>());
}

void
ItemData::AppendTokens(std::vector<int> tokenList) {
    tokens.insert(tokens.end(), tokenList.begin(), tokenList.end());
    std::sort(tokens.begin(), tokens.end(), std::less<int>());
}

std::vector<int>
ItemData::GetTokens() {
    return tokens;
}

void
ItemData::SetTokens(std::vector<int> tokenList) {
    tokens.swap(tokenList);
    std::sort(tokens.begin(), tokens.end(), std::less<int>());
}

ItemData*
ItemData::Clone() {
    ItemData* rule   = new ItemData{};
    rule->id         = id;
    rule->left       = left;
    rule->right      = right;
    rule->dot        = dot;
    rule->next_state = next_state;
    rule->root       = root;
    rule->tokens     = tokens;
    return rule;
}

bool
ItemData::operator==(const ItemData& other) {
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
