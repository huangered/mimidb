#ifndef _sema_hpp_
#define _sema_hpp_

#include "lex/lexer.hpp"
#include "sema/dictionary.hpp"
#include "util/generic.hpp"

#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
#include <ostream>


struct SemaTokenData {
	int id;
	bool sema;
	yih::String name;
	LexToken lexToken;

public:
	SemaTokenData(int _id, bool _sema, yih::String _name) {
		id = _id;
		sema = _sema;
		name = _name;
	}

	SemaTokenData(int _id, bool _sema, LexToken _lexToken) {
		id = _id;
		sema = _sema;
		lexToken = _lexToken;
	}

	int Compare(const SemaTokenData* token) {
		int i;
		if ((i = (sema - token->sema)) != 0) {
			return i;
		}

		if (sema) {
			return name.Compare(token->name);
		}
		else {
			return lexToken->compare(*token->lexToken);
		}
	}
};

typedef SemaTokenData* SemaToken;
typedef std::vector<SemaToken> SemaTokenList;

class NodeData;

typedef NodeData* Node;

class NodeData {
	std::vector<Node> _nodes;
	const SemaToken _token;

public:
	NodeData(SemaToken token) :_token{ token } {}

	void addAll(std::vector<Node> nodes) {
		for (Node n : nodes) {
			_nodes.push_back(n);
		}
	}

	SemaToken getToken() {
		return _token;
	}
};


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
	SemaTokenList tokens;

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

	void SetToken(SemaToken token) {
		tokens.push_back(token);
	}

	void AppendTokens(SemaTokenList tokens) {

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

	SemaTokenList getTokens() {
		return tokens;
	}

	void setTokens(SemaTokenList tokens) {
		this->tokens = tokens;
	}

	int Compare(RuleData& other) {
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

		auto j = [](SemaToken l, SemaToken r) -> bool {
			return l->id < r->id;
		};

		std::sort(tokens.begin(), tokens.end(), j);
		std::sort(other.tokens.begin(), other.tokens.end(), j);

		for (int j = 0; j < tokens.size(); j++) {
			if ((i = tokens[j]->Compare(other.tokens[j])) != 0) {
				return i;
			}
		}

		return dot - other.dot;
	}

	// 用户自定义的规则
	Node format(SemaToken token, std::vector<Node> children) {
		Node n = new NodeData{token};
		n->addAll(children);
		return n;
	}
};

typedef RuleData* Rule;
typedef std::vector<Rule> RuleList;

struct StateItemData {
	int id;
	bool acc;
};

typedef StateItemData* StateItem;

class StateData {
	int _id;
	RuleList _rules;

public:
	StateData(int id) :_id{ id } {}
	
	RuleList GetRules() {
		return _rules;
	}

	void ResetRules(RuleList rules) {
		_rules.swap(rules);
	}

	void Add(Rule rule) {
		auto cmp = [rule](Rule r) -> bool {
			return r->Compare(*rule) == 0;
		};

		auto iter = std::find_if(_rules.begin(), _rules.end(), cmp);

		if (iter == _rules.end()) {
			_rules.push_back(rule);
		}
	}

	void Add(std::set<Rule> rules) {
		for (auto iter = rules.begin(); iter != rules.end(); iter++) {
			Add(*iter);
		}
	}

	bool MatchRule(RuleList rules1) {
		for (auto rules = rules1.begin(); rules != rules1.end(); rules++) {
			Rule r = *rules;
			auto match = [&](Rule rule)->bool {
				return rule->Compare(*r) == 0;
			};
			auto iter = std::find_if(_rules.begin(), _rules.end(), match);
			if (iter == _rules.end()) {
				return false;
			}
		}
		return true;
	}

	int GetId() {
		return _id;
	}
};

typedef StateData* State;
typedef std::vector<State> StateList;

class StateCollection {
	StateList stateList;
public:
	int Size();
	bool IsEmpty(int stateId);
	void Add(State state);
	void Add(int stateId, Rule rule);
	RuleList GetRules(int stateId);
	State GetState(int stateId);
};

struct RecordData {
	bool acc;
	bool state;
	int id;

	friend std::ostream& operator<<(std::ostream& os, const RecordData& dt) {
		if (dt.id == -1) {
			os << "  ";
			return os;
		}
		if (dt.acc) {
			os << "acc";
			return os;
		}
		if (dt.state) {
			os << "s" << dt.id;
		}
		else {
			os << "r" << dt.id;
		}
		return os;
	}
};

typedef RecordData* Record;

class GotoTable {
private:
	int _row, _col;
	Record** _data;
public:
	GotoTable(int row, int col) {
		_row = row;
		_col = col;
		_data = new Record * [row];
		for (int i = 0; i < row; i++) {
			_data[i] = new Record[col]{};
			for (int j = 0; j < col; j++) {
				auto q = _data[i] + j;
				*q = nullptr;
			}
		}
	}

	void add(int stateId, int tokenId, int nextStateId) {
		Record* record = &_data[stateId][tokenId];
		if (*record == nullptr) {
			*record = new RecordData{ .state = true , .id = nextStateId };
		}
	}

	Record find(int stateId, int tokenId) {		
		if (stateId<0 || stateId>_row || tokenId< 0 || tokenId>_col) {
			return nullptr;
		}

		auto record = _data[stateId][tokenId];
		return record;
	}

	void print() {
		
		for (int i{ 0 }; i < _col;i++) {
			std::cout << " " << i << "|";
		}
		std::cout << std::endl;
		for (int stateId = 0; stateId != _row; stateId++) {
			std::cout << stateId << ":";
			for (int i{ 0 }; i < _col;i++) {
				Record record = _data[stateId][i];
				if (record != nullptr) {
					std::cout << *record;
				}
				else {
					std::cout << "  ";
				}
				std::cout<<"|";
			}
			std::cout<<std::endl;
		}
	}
};

class ActionTable {
	int _row, _col;
	Record** _data;
public:
	ActionTable(int row, int col) {
		_row = row;
		_col = col;
		_data = new Record * [row];
		for (int i = 0; i < row; i++) {
			_data[i] = new Record[col]{};
			for (int j = 0; j < col; j++) {
				_data[i][j] = nullptr;
			}
		}
	}

	Record find(int stateId, int lexTokenId) {
		if (stateId<0 || stateId>_row || lexTokenId< 0 || lexTokenId>_col) {
			return nullptr;
		}

		auto record = _data[stateId][lexTokenId];
		return record;
	}

	void addRule(int stateId, int lexTokenId, int ruleId, bool acc) {
		Record* r = &_data[stateId][lexTokenId];
		if (*r == nullptr) {
			*r = new RecordData{};
		}
		(*r)->id = ruleId;
		(*r)->state = false;
		(*r)->acc = acc;
	}

	void add(int stateId, int lexTokenId, int nextStateId) {
		Record* r = &_data[stateId][lexTokenId];
		if (*r == nullptr) {
			*r = new RecordData{};
		}
		(*r)->id = nextStateId;
		(*r)->state = true;
	}

	void print() {
		for (int i{ 0 }; i < _col; i++) {
			std::cout << " " << i << "|";
		}
		std::cout << std::endl;
		for (int stateId = 0; stateId != _row; stateId++) {
			std::cout << stateId << ":";
			for (int i{ 0 }; i < _col; i++) {
				Record record = _data[stateId][i];
				if (record != nullptr) {
					std::cout << *record;
				}
				else {
					std::cout << "  ";
				}
				std::cout << "|";
			}
			std::cout << std::endl;
		}
	}
};

class FirstSet {
private:
	std::vector<SimpleRule> _rules;

	std::map<int, SemaToken> _semaTokens;

	std::map<int, std::set<int>> _firstSet;

	std::map<int, SemaToken> _terminals;
	std::map<int, SemaToken> _nonTerminals;

public:
	FirstSet(std::vector<SimpleRule> rules) {
		_rules = rules;
		// 更新 _semaTokens;
		for (SimpleRule rule : _rules) {
			SemaToken left = rule->left;
			_semaTokens[left->id] = left;

			for (SemaToken r : rule->right) {
				_semaTokens[r->id] = r;
			}
		}
	}

	SemaTokenList Find(SemaToken nonTerminal) {
		std::set<int> r = _firstSet[nonTerminal->id];
		SemaTokenList rList;
		for (int _r : r) {
			rList.push_back(_semaTokens[_r]);
		}
		return rList;
	}

	SemaTokenList Find(SemaTokenList tokens, SemaTokenList extra) {
		if (tokens.size() == 0) {
			return extra;
		}
		for (SemaToken c : tokens) {
			if (!c->sema) {
				return { c };
			}
			return Find(tokens[0]);
		}
		return {};
	}

	void Gen() {
		int count;
		do {
			count = 0;

			for (SimpleRule rule : _rules) {
				SemaToken left = rule->left;

				if (_firstSet.count(left->id) == 0) {
					_firstSet[left->id] = {};
				}

				std::set<int> c{};
				if (!rule->right[0]->sema) {
					c.insert(rule->right[0]->id);
				}
				else {
					SemaToken firstRight = rule->right[0];
					if (_firstSet.count(firstRight->id) > 0) {
						auto tokens = _firstSet[firstRight->id];
						c.insert(tokens.begin(), tokens.end());
					}
				}
				for (int cc : c) {
					if (_firstSet[left->id].count(cc) == 0) {
						_firstSet[left->id].insert(cc);
						count++;
					}
				}
			}

		} while (count > 0);
	}

	void print() {
		for (auto entry = _firstSet.begin(); entry != _firstSet.end(); entry++)
		{
			std::cout << _semaTokens[entry->first]->name.Data() << " => ";
			for (int i : entry->second) {
				std::cout << _semaTokens[i]->lexToken->tok << ",";
			}
			std::cout << std::endl;
		}
	}
};

class Parser {
private:
	RuleList _rules;
	int _maxState;
	GotoTable* _gotoTable;
	ActionTable* _actionTable;
	FirstSet* _firstSet;
	StateCollection* _stateList;

	SemaTokenList _terminals;
	SemaTokenList _nonTerminals;
public:
	Parser(std::vector<SimpleRule> rules, SemaTokenList terminals, SemaTokenList nonTerminals);
	~Parser();
	void GenerateParseTable(void);
	Node Parse(std::vector<LexToken> input);
private:
	void handleState(int i);
	void generateTable(void);
	void expandRules(State state);
	int searchSameState(RuleList newStateRules);

	bool reduce(std::stack<StateItem>& states, std::stack<Node>& syms, Record curRecord);
	bool eatToken(std::stack<StateItem>& states, std::stack<Node>& syms, std::stack<SemaToken>& input);
};

#endif
