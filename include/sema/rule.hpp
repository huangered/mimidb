#ifndef _rule_hpp_
#define _rule_hpp_

#include "lex/lexer.hpp"
#include "sema/node.hpp"
#include <vector>

class SemaTokenData;
typedef SemaTokenData* SemaToken;
typedef std::vector<SemaToken> SemaTokenList;

struct SimpleRuleData {
	int id;
	SemaToken left;
	SemaTokenList right;
};

typedef SimpleRuleData* SimpleRule;

static SimpleRule make_rule(int id, SemaToken left, SemaTokenList right) {
	SimpleRule rule = new SimpleRuleData{ id, left, right };
	return rule;
}

struct RuleData {
	int id;

	int dot;
	int cur_state;
	int next_state;

	bool root;

	SemaToken left;
	SemaTokenList right;
	// look ahead 检查
	std::vector<Tok> tokens;

	bool isDotEnd() {
		return dot == right.size();
	}

	SemaToken getTokenAfterDot() {
		return right[dot];
	}

	SemaTokenList GetStringAfterDot() {
		SemaTokenList tokens;
		for (int i = dot + 1; i != right.size(); i++) {
			tokens.push_back(right[i]);
		}
		return tokens;
	}

	void SetToken(Tok token) {
		tokens.push_back(token);
	}

	void AppendTokens(std::vector<Tok> tokens) {
		this->tokens.insert(this->tokens.end(), tokens.begin(), tokens.end());
	}

	RuleData* clone() {
		RuleData* rule = new RuleData{};
		rule->id = id;
		rule->left = left;
		rule->right = right;
		rule->dot = dot;
		rule->root = root;
		rule->tokens = tokens;
		return rule;
	}

	std::vector<Tok> getTokens() {
		return tokens;
	}

	void setTokens(std::vector<Tok> tokens) {
		this->tokens = tokens;
	}

	int Compare(RuleData& other);

	// 用户自定义的规则
	Node format(SemaToken token, std::vector<Node> children) {
		Node n = new NodeData{ token };
		n->addAll(children);
		return n;
	}
};

typedef RuleData* Rule;
typedef std::vector<Rule> RuleList;

#endif // !_rule_hpp_
