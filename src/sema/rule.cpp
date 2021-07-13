#include "sema/rule.hpp"
#include "sema/sema.hpp"

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

	auto j = [](Tok l, Tok r) -> bool {
		return l < r;
	};

	std::sort(tokens.begin(), tokens.end(), j);
	std::sort(other.tokens.begin(), other.tokens.end(), j);

	for (int j = 0; j < tokens.size(); j++) {
		if ((i = tokens[j] - other.tokens[j]) != 0) {
			return i;
		}
	}

	return dot - other.dot;
}