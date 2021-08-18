#include "table.hpp"
#include "sema.hpp"
#include "debug.hpp"

GotoTable::GotoTable(int row, int col)
    : _row{ row }
    , _col{ col } {
    _data = new Record*[row];
    for (int i{ 0 }; i < row; i++) {
        _data[i] = new Record[col]{};
        for (int j = 0; j < col; j++) {
            auto q = _data[i] + j;
            *q     = nullptr;
        }
    }
}

GotoTable::GotoTable(const GotoTable& tb) {
    _row  = tb._row;
    _col  = tb._col;
    _data = new Record*[_row];
    for (int i{ 0 }; i < _row; i++) {
        _data[i] = new Record[_col]{};
        for (int j = 0; j < _col; j++) {
            auto q = _data[i] + j;
            *q     = nullptr;
        }
    }
}

GotoTable::~GotoTable() {
    for (int i{ 0 }; i < _row; i++) {
        for (int j{ 0 }; j < _col; j++) {
            Record* r = _data[i] + j;
            if (*r != nullptr) {
                delete *r;
            }
        }
        delete[] _data[i];
    }
    delete[] _data;
}

void
GotoTable::Add(int stateId, int tokenId, int nextStateId) {
    Record* record = &_data[stateId][tokenId];
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

    auto record = _data[stateId][tokenId];
    return record;
}

void
GotoTable::Print() {
#ifdef _log_
    for (int i{ 0 }; i < _col; i++) {
        std::cout << " " << i << "|";
    }
    std::cout << std::endl;
    for (int stateId{ 0 }; stateId != _row; stateId++) {
        std::cout << stateId << ":";
        for (int i{ 0 }; i < _col; i++) {
            Record record = _data[stateId][i];
            if (record != nullptr) {
                std::cout << *record;
            } else {
                std::cout << "  ";
            }
            std::cout << "|";
        }
        std::cout << std::endl;
    }
#endif
}

ActionTable::ActionTable(int row, int col)
    : _row{ row }
    , _col{ col } {
    _data = new Record*[row];
    for (int i = 0; i < row; i++) {
        _data[i] = new Record[col]{};
        for (int j = 0; j < col; j++) {
            _data[i][j] = nullptr;
        }
    }
}

ActionTable::ActionTable(const ActionTable& tb) {
    _row  = tb._row;
    _col  = tb._col;
    _data = new Record*[_row];
    for (int i = 0; i < _row; i++) {
        _data[i] = new Record[_col]{};
        for (int j = 0; j < _col; j++) {
            _data[i][j] = nullptr;
        }
    }
}

ActionTable::~ActionTable() {
    for (int i{ 0 }; i < _row; i++) {
        for (int j{ 0 }; j < _col; j++) {
            Record* r = _data[i] + j;
            if (*r != nullptr) {
                delete *r;
            }
        }
        delete _data[i];
    }
    delete[] _data;
}

Record
ActionTable::Find(int stateId, int lexTokenId) {
    if (stateId < 0 || stateId > _row || lexTokenId < 0 || lexTokenId > _col) {
        return nullptr;
    }

    auto record = _data[stateId][lexTokenId];
    return record;
}

void
ActionTable::AddRule(int stateId, int lexTokenId, int ruleId, bool acc) {
    Record* r = &_data[stateId][lexTokenId];
    if (*r == nullptr) {
        *r = new RecordData{};
    }
    (*r)->id    = ruleId;
    (*r)->state = false;
    (*r)->acc   = acc;
}

void
ActionTable::Add(int stateId, int lexTokenId, int nextStateId) {
    Record* r = &_data[stateId][lexTokenId];
    if (*r == nullptr) {
        *r = new RecordData{};
    }
    (*r)->id    = nextStateId;
    (*r)->state = true;
}

void
ActionTable::Print() {
#ifdef _log_
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
            } else {
                std::cout << "  ";
            }
            std::cout << "|";
        }
        std::cout << std::endl;
    }
#endif
}
