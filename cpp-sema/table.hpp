#ifndef _table_hpp_
#define _table_hpp_

class RecordData;
typedef RecordData* Record;

class GotoTable {
private:
    int _row, _col;
    Record** _data;

public:
    GotoTable(int row, int col);
    GotoTable(const GotoTable&);
    ~GotoTable();
    void Add(int stateId, int semaId, int nextStateId);

    Record Find(int stateId, int semaId);

    void Print();
};

class ActionTable {
    int _row, _col;
    Record** _data;

public:
    ActionTable(int row, int col);
    ActionTable(const ActionTable&);
    ~ActionTable();
    Record Find(int stateId, int lexTokenId);

    void AddRule(int stateId, int lexTokenId, int ruleId, bool acc);

    void Add(int stateId, int lexTokenId, int nextStateId);

    void Print();
};

#endif
