#ifndef _table_hpp_
#define _table_hpp_

#include <iostream>

class RecordData;
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

	void add(int stateId, int tokenId, int nextStateId);

	Record find(int stateId, int tokenId);

	void print();
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

	Record find(int stateId, int lexTokenId);

	void addRule(int stateId, int lexTokenId, int ruleId, bool acc);

	void add(int stateId, int lexTokenId, int nextStateId);

	void print();
};

#endif
