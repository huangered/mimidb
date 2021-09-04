#include "rule.hpp"
#include "sema.hpp"

RuleList Rules;

bool
ItemData::IsDotEnd() {
    return dot == rule->right.size();
}

Symbol
ItemData::GetTokenAfterDot() {
    return rule->right[dot];
}

SymbolList
ItemData::GetStringAfterDot() {
    SymbolList t{ rule->right.begin() + dot + 1, rule->right.end() };
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
    rule->rule       = this->rule;
    rule->id         = id;
    rule->dot        = dot;
    rule->next_state = next_state;
    rule->tokens     = tokens;
    return rule;
}

bool
ItemData::operator==(const ItemData& other) {
    if (rule->left != other.rule->left) {
        return false;
    }

    if (!SymbolListEqual(rule->right, other.rule->right)) {
        return false;
    }

    if (tokens != other.tokens) {
        return false;
    }

    return dot == other.dot;
}
