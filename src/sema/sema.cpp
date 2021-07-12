﻿#include "sema/sema.hpp"


static bool SemaTokenListEqual(SemaTokenList& left, SemaTokenList& right);

template <typename pr>
std::vector<Rule*>
findSameRule(std::vector<Rule*>::iterator begin, std::vector<Rule*>::iterator end, pr pred) {
	std::vector<Rule*> rules;
	auto iter = std::find_if(begin, end, pred);
	if (iter != end) {
		rules.push_back(*iter);
	}
	return rules;
}
// state collection

int
StateCollection::Size() {
	return stateList.size();
}
	
bool
StateCollection::IsEmpty(int stateId) {
	return stateList[stateId]->getRules().size() == 0;
}

void
StateCollection::Add(State state) {
	stateList.push_back(state);
}

void
StateCollection::Add(int stateId, Rule* rule) {
	stateList[stateId]->add(rule);
}

std::vector<Rule*>
StateCollection::getRules(int stateId) {
	return stateList[stateId]->getRules();
}

State
StateCollection::getState(int stateId) {
	return stateList[stateId];
}

// end



Parser::Parser(std::vector<Rule1> rules, SemaTokenList terminals, SemaTokenList nonTerminals) {
	_maxState = 0;
	_terminals = terminals;
	_nonTerminals = nonTerminals;
	_firstSet = new FirstSet(rules);
	_stateList = new StateCollection();
	_stateList->Add(new StateData{ 0 });
	for (Rule1 rule : rules) {
		Rule* r = new Rule{};
		r->id = rule->id;
		r->left = rule->left;
		r->right = rule->right;
		_rules.push_back(r);
	}
	_rules[0]->root = true;
	Rule* rule = _rules[0]->clone();
	rule->SetToken(terminals[terminals.size() - 1]);
	_stateList->Add(0, rule);
}

Parser::~Parser() {
	delete _gotoTable;
	delete _actionTable;
	delete _firstSet;
	delete _stateList;
}

void
Parser::GenerateParseTable(void) {
	_firstSet->Gen();
	for (int i = 0; i < _stateList->Size(); i++) {
		if (_stateList->IsEmpty(i)) {
			break;
		}

		handleState(i);
	}

	generateTable();
}

std::vector<Node*>
Parser::Parse(std::vector<LexToken*> input) {
	// init stach
	std::stack<StateItem> state_stack;
	state_stack.push(new StateItemData{ 0, false });
	std::stack<Node*> token_stack;
	std::stack<SemaToken> input_stack;

	token_stack.push(new Node{ new SemaTokenData{-2, false, {Tok::Money}} });
	for (auto iter = input.rbegin(); iter != input.rend(); iter++) {
		input_stack.push(new SemaTokenData(-2, false, **iter));
	}


	while (!state_stack.top()->acc) {
		bool op = reduce(state_stack, token_stack, nullptr);
		op != eatToken(state_stack, token_stack, input_stack);

		if (!op) {
			std::cout << "no action" << std::endl;
			break;
		}
	}
	return { token_stack.top() };
}

// === private part ===
void
Parser::handleState(int stateId) {
	State state = _stateList->getState(stateId);
	// 1. 扩展规则
	expandRules(state);
	// 2. 构建新状态
	std::map<int, SemaToken> tokens;
	for (Rule* rule : state->getRules()) {
		if (!rule->isDotEnd()) {
			SemaToken token = rule->getTokenAfterDot();
			tokens[token->id] = token;
		}
	}

	for (auto iter = tokens.begin(); iter != tokens.end(); iter++) {
		SemaToken token = iter->second;

		std::vector<Rule*> movedRules;
		std::vector<Rule*> newStateRules;
		for (Rule* r : state->getRules()) {
			if (!r->isDotEnd() && r->right[r->dot]->id == token->id) {
				movedRules.push_back(r);

				Rule* n = r->clone();
				n->dot++;
				newStateRules.push_back(n);
			}
		}

		// 寻找相同的状态集合。
		int stateId1 = searchSameState(newStateRules);

		if (stateId1 == -1) {
			// 没找到
			_maxState++;
			std::for_each(movedRules.begin(), movedRules.end(), [&](Rule* r) {r->next_state = _maxState; });
			if (_stateList->Size() <= _maxState) {
				for (int i = _stateList->Size(); i <= _maxState; i++) {
					_stateList->Add(new StateData(i));
				}
			}
		for(Rule* newRule :	newStateRules){
				_stateList->getState(_maxState)->add(newRule);
			};
		}
		else {
			// 找到了
			for (Rule* r : movedRules) {
				r->next_state = stateId1;
			}
		}
	}
}

void
Parser::generateTable(void) {
	_gotoTable = new GotoTable(_stateList->Size(), 10);
	_actionTable = new ActionTable(_stateList->Size() , Tok::Unknown);

	for (int i = 0; i < _stateList->Size(); i++) {
		for (Rule* r : _stateList->getRules(i)) {
			if (r->isDotEnd()) {
				// find rule id
				// add r1 in action
				for (int g = 0; g < _rules.size(); g++) {
					Rule* c = _rules[g];
					if (c->left->id==r->left->id && SemaTokenListEqual(c->right, r->right)) {
						for (SemaToken token : r->getTokens()) {
							_actionTable->addRule(i, token->lexToken.tok, g, r->root);
						}
					}
				}
			}
			else {
				SemaToken w = r->right[r->dot];
				if (w->sema) {
					// update goto
					_gotoTable->add(i, w->id, r->next_state);
				}
				else {
					// update action
					_actionTable->add(i, w->lexToken.tok, r->next_state);
				}
			}
		}
	}
	_actionTable->print();
	_gotoTable->print();
}

void
Parser::expandRules(State state) {
	int count = 0;

	for (;;) {
		count = 0;
		std::set<Rule*> copied;

		std::vector<Rule*> mock{ state->getRules() };


		for (Rule* r : mock) {
			r->cur_state = state->GetId();
			if (r->isDotEnd()) {
				continue;
			}
			SemaToken word = r->getTokenAfterDot();
			if (word->sema) {
				// non terminals
				// update state list

				auto match1 = [word](Rule* rule) -> bool {
					return rule->left->id == word->id;
				};
				std::vector<Rule*> match = findSameRule(_rules.begin(), _rules.end(), match1);
				for (Rule* rule : match) {
					SemaTokenList tokens = _firstSet->Find(rule->GetStringAfterDot(), rule->getTokens());

					Rule* copy = rule->clone();
					copy->dot = 0;
					copy->setTokens(tokens);
					// 如果是新rule
					auto m2 = [copy](Rule* rule)-> bool {
						return rule->compare(*copy) == 0;
					};
					std::vector<Rule*> gg = state->getRules();
					auto iter2 = findSameRule(gg.begin(),
						gg.end(),
						m2
					);
					if (iter2.size() == 0) {
						copied.insert(copy);
						count++;
					}
				}
			}
		}

		if (count == 0) {
			break;
		}
		else {
			state->add(copied);
		}
	}

	// 合并 state 里的 rules

}

int
Parser::searchSameState(std::vector<Rule*> newStateRules) {
	for (int i{ 0 }; i < _stateList->Size(); i++) {
		State state = _stateList->getState(i);
		if (state->matchRule(newStateRules)) {
			return i;
		}
	}
	return -1;
}

bool
SemaTokenListEqual(SemaTokenList& left, SemaTokenList& right) {
	if (left.size() != right.size()) {
		return false;
	}

	std::sort(left.begin(), left.end(), [](SemaToken l, SemaToken r) {
		return l->id < r->id;
		});

	std::sort(right.begin(), right.end(), [](SemaToken l, SemaToken r) {
		return l->id < r->id;
		});

	for (int i{ 0 }; i < left.size(); i++) {
		if (left[i]->id != right[i]->id) {
			return false;
		}
	}

	return true;
}

bool
Parser::reduce(std::stack<StateItem> states, std::stack<Node*> syms, Record curRecord) {
	bool op = false;
	Record record = curRecord;
	StateItem curStateId = states.top();
	Node* curNode = syms.top();
	if (curRecord==nullptr && !curNode->getToken()->sema) {
		record = _actionTable->find(curStateId->id, curNode->getToken()->id);
	}
	if (record !=nullptr && !record->state) {
		op = true;
		Rule* rule = _rules[record->id];
		std::vector<Node*> child;
		for (int i = 0; i < rule->right.size(); i++) {
			child.push_back(syms.top());
			syms.pop();
			states.pop();
		}
		Node* left = rule->format(rule->left, child);
		syms.push(left);

		// find goto table
		curStateId = states.top();

		// 找到 acc 事件，结束解析
		if (rule->root) {
			StateItem acc = new StateItemData{ 0 };
			acc->acc = true;
			states.push(acc);
			return op;
		}

		int nextStateId = _gotoTable->find(curStateId->id, rule->left->id)->id;
		states.push(new StateItemData{ nextStateId });
	}
	return op;
}
bool
Parser::eatToken(std::stack<StateItem> states, std::stack<Node*> syms, std::stack<SemaToken> input) {
	bool op = false;
	StateItem curStateId = states.top();
	SemaToken token = input.top();
	Record record = _actionTable->find(curStateId->id, token->lexToken.tok);
	if (record != nullptr) {
		op = true;
		if (record->state) {
			states.push(new StateItemData{ record->id });
			syms.push(new Node(token));
			input.pop();
			return op;
		}
		else {
			return reduce(states, syms, record);
		}
	}
	return op;
}