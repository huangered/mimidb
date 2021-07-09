#include "sema/sema.hpp"


Parser::Parser(std::vector<Rule*> rules) {

}

Parser::~Parser() {
	delete gotoTable;
	delete actionTable;
	delete firstSet;
	delete stateList;
}

void
Parser::GenerateParseTable(void) {
	firstSet->gen();
	for (int i = 0; i < stateList->Size(); i++) {
		if (stateList->IsEmpty(i)) {
			break;
		}

		handleState(i);
	}

	generateTable();
}

std::vector<Node*>
Parser::Parse(std::vector<LexToken*> input) {
	std::vector<Node*> p;
	return p;
}

// === private part ===
void
Parser::handleState(int i) {
}

void
Parser::generateTable(void) {
	gotoTable = new GotoTable(stateList->Size());
	actionTable = new ActionTable(stateList->Size());
}