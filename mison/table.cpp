#include "table.hpp"
#include "sema.hpp"
#include "debug.hpp"

GotoTable::GotoTable(int row, int col)
    : _row{ row }
    , _col{ col } {
      _data = new Record[row * col]();
}

GotoTable::~GotoTable() {
  for (int i{ 0 }; i < _row * _col; i++) {
    Record r = _data[i];
    if (r != nullptr)      {
      delete r;
    }
  }
  delete[] _data;
}

void
GotoTable::Add(int stateId, int tokenId, int nextStateId) {
    Record* record = &_data[stateId * _col +tokenId];
    if (*record == nullptr) {
        *record = new RecordData{};
    }

    (*record)->id    = nextStateId;
    (*record)->state = true;
    (*record)->acc   = false;
}

Record
GotoTable::Find(int stateId, int tokenId) {
    if (stateId < 0 || stateId > _row || tokenId < 0 || tokenId > _col) {
        return nullptr;
    }

    auto record = _data[stateId * _col + tokenId];
    return record;
}

void
GotoTable::Print() {
#ifdef _log_
    printf("Goto table:\n    ");

    for (int i{ 0 }; i < _col; i++) {
        printf("%3d|", i);
    }
    printf("\n");
    for (int stateId{ 0 }; stateId != _row; stateId++) {
        printf("%3d:", stateId);
        for (int i{ 0 }; i < _col; i++) {
            Record record = _data[stateId * _col + i];
            if (record != nullptr) {
                printf("%3d", record->id);
            } else {
                printf("   ");
            }
            printf("|");
        }
        printf("\n");
    }
#endif
}

ActionTable::ActionTable(int row, int col)
    : _row{ row }
    , _col{ col } {
    _data = new Record[ row * col ]();
}

ActionTable::~ActionTable() {
    for(int i {0} ; i < _row * _col;i++){
      Record r = _data[i];
      if( r != nullptr){
	delete r;
      }
    }

    delete[] _data;
}

Record
ActionTable::Find(int stateId, int lexTokenId) {
    if (stateId < 0 || stateId > _row || lexTokenId < 0 || lexTokenId > _col) {
        return nullptr;
    }

    auto record = _data[stateId * _col + lexTokenId];
    return record;
}

void
ActionTable::AddRule(int stateId, int lexTokenId, int ruleId, bool acc) {
    Record* r = &_data[ stateId* _col + lexTokenId];
    if (*r == nullptr){
      *r = new RecordData{};
    }
    (*r)->id    = ruleId;
    (*r)->state = false;
    (*r)->acc   = acc;
    
}

void
ActionTable::Add(int stateId, int lexTokenId, int nextStateId) {
    Record* r = &_data[ stateId * _col + lexTokenId];
    if (*r == nullptr) {
      *r = new RecordData{};
    }
    (*r)->id = nextStateId;
    (*r)->state = true;
}

void
ActionTable::Print() {
#ifdef _log_
    printf("Action table:\n     ");
    for (int i{ 0 }; i < _col; i++) {
        printf("%4d|", i);
    }
    printf("\n");
    for (int stateId = 0; stateId != _row; stateId++) {
        printf("%4d:", stateId);
        for (int i{ 0 }; i < _col; i++) {
	  Record record = _data[stateId *_col + i];
            if (record != nullptr) {
                if (record->acc) {
                    printf("acc ");
                } else {
                    printf("%4d", record->state ? record->id : -record->id);
                }
            } else {
                printf("    ");
            }
            printf("|");
        }
        printf("\n");
    }
#endif
}
