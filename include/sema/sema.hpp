#ifndef _sema_hpp_
#define _sema_hpp_

#include <vector>
#include "lex/lexer.hpp"
#include <map>

struct SemaToken {
	bool sema;
	yih::String name;
	LexToken lexToken;
};

class Rule1 {
private:
	int _id;
	SemaToken* _left;
	std::vector<SemaToken*> _right;
public:
	Rule1(int id, SemaToken* left, std::vector<SemaToken*> right) {
		_id = id;
		_left = left;
		_right.swap(right);
	}
	~Rule1() {
		delete _left;
		for (SemaToken* p : _right) {
			delete p;
		}
	}
};

struct Rule {
	int id;

	int dot;
	int cur_state;
	int next_state;

	bool root;

	SemaToken* left;
	std::vector<SemaToken*> right;

};

class State {
	int id;
	std::vector<Rule*> rules;
};

class StateList {
	std::vector<State*> stateList;
public:
	int Size();
	bool IsEmpty(int i);
};

class Node {
	int i;
};

template<class p1, class p2, class p3>
class Directory {
};

template<class p1, class p2, class p3>
class Directory<p1, p2, p3*> {
public:
	//template<class a1, class b1>
	struct Entry {
		p1 param1;
		p2 param2;

		Entry(p1 a, p2 b) {
			param1 = a;
			param2 = b;
		}

		bool operator<(Entry const& right) const {
			int i = param1 - right.param1;
			if (i != 0) {
				return i < 0 ? true : false;
			}

			return param2 < right.param2;
		}
	};

	std::map<Entry, p3*> data;

public:
	Directory() {}
	~Directory() {
		for (auto g = data.begin(); g != data.end(); g++) {
			delete g->second;
		}
	}
	void put(p1 a, p2 b, p3* c) {
		Entry entry{ a,b };
		std::pair<Entry, p3*> p = std::make_pair(entry, c);
		data.insert(p);
	}

	std::pair<bool, p3*> get(p1 a, p2 b) {
		Entry entry{ a,b };
		auto r = data.find(entry);
		if (r != data.end()) {
			return std::make_pair(true, r->second);
		}

		return std::make_pair(false, nullptr);
	}
};

class GotoTable {
private:
	
public:
	GotoTable(int num);
};

class ActionTable {
public:
	ActionTable(int num);
};

class FirstSet {
public:
	void gen();
};

class Parser {
private:
	std::vector<Rule*> rules;
	int maxState;
	GotoTable* gotoTable;
	ActionTable* actionTable;
	FirstSet* firstSet;
	StateList* stateList;
public:
	Parser(std::vector<Rule*> rules);
	~Parser();
	void GenerateParseTable(void);
	std::vector<Node*> Parse(std::vector<LexToken*> input);
private:
	void handleState(int i);
	void generateTable(void);
};

#endif