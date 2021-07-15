#include "sema/table.hpp"
#include "sema/sema.hpp"

void
GotoTable::Add(int stateId, int tokenId, int nextStateId) {
    Record* record = &_data[stateId][tokenId];
    if (*record == nullptr) {
        *record = new RecordData{.state = true, .id = nextStateId};
    }
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

    for (int i{0}; i < _col; i++) {
        std::cout << " " << i << "|";
    }
    std::cout << std::endl;
    for (int stateId = 0; stateId != _row; stateId++) {
        std::cout << stateId << ":";
        for (int i{0}; i < _col; i++) {
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
    (*r)->id = ruleId;
    (*r)->state = false;
    (*r)->acc = acc;
}

void
ActionTable::Add(int stateId, int lexTokenId, int nextStateId) {
    Record* r = &_data[stateId][lexTokenId];
    if (*r == nullptr) {
        *r = new RecordData{};
    }
    (*r)->id = nextStateId;
    (*r)->state = true;
}

void
ActionTable::Print() {
    for (int i{0}; i < _col; i++) {
        std::cout << " " << i << "|";
    }
    std::cout << std::endl;
    for (int stateId = 0; stateId != _row; stateId++) {
        std::cout << stateId << ":";
        for (int i{0}; i < _col; i++) {
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
}
