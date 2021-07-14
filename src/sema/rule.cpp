#include "sema/rule.hpp"
#include "sema/sema.hpp"

void
RuleData::SetToken(Tok token){
    tokens.push_back(token);
    auto j = [](Tok l, Tok r) -> bool {
        return l < r;
    };
    std::sort(tokens.begin(),tokens.end(),j);
}

void
RuleData::AppendTokens(std::vector<Tok> tokenList) {
    tokens.insert(tokens.end(), tokenList.begin(), tokenList.end());
    
    auto j = [](Tok l, Tok r) -> bool {
        return l < r;
    };
    std::sort(tokens.begin(),tokens.end(),j);
}

void
RuleData::SetTokens(std::vector<Tok> tokenList) {
    tokens.swap(tokenList);
    auto j = [](Tok l, Tok r) -> bool {
        return l < r;
    };
    std::sort(tokens.begin(),tokens.end(),j);
}

int
RuleData::Compare(RuleData& other) {
	int i;
	if ((i = left->Compare(other.left)) != 0) {
		return i;
	}

	if ((i = (right.size() - other.right.size())) != 0) {
		return i;
	}

	for (int j = 0; j < right.size(); j++) {
		if ((i = right[j]->Compare(other.right[j])) != 0) {
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
