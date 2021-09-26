#include "rule.hpp"
#include "sema.hpp"
#include <set>

RuleList Rules;

bool
ItemData::IsDotEnd() {
    return dot == Rules[id]->right.size();
}

Symbol
ItemData::GetTokenAfterDot() {
    return Rules[id]->right[dot];
}

SymbolList
ItemData::GetStringAfterDot() {
    SymbolList t{ Rules[id]->right.begin() + dot + 1, Rules[id]->right.end() };
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
    Item item        = new ItemData{};
    item->id         = id;
    item->dot        = dot;
    item->next_state = next_state;
    item->tokens     = tokens;
    return item;
}

bool
ItemData::operator==(const ItemData& other) {
    if (id != other.id) {
        return false;
    }

    if (tokens != other.tokens) {
        return false;
    }

    return dot == other.dot;
}
