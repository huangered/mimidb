#include "state.hpp"
#include <algorithm>

StateData::StateData(int id)
    : _id{ id } {
}

StateData::~StateData() {
    for (Item item : _items) {
        //delete item;
    }
}

ItemList
StateData::GetItems() {
    return _items;
}

void
StateData::ResetItems(ItemList& items) {
    _items.swap(items);
}

void
StateData::Add(Item item) {
    auto cmp = [item](Item r) -> bool { return *r == *item; };

    auto iter = std::find_if(_items.begin(), _items.end(), cmp);

    if (iter == _items.end()) {
        _items.push_back(item);
    }
}

void
StateData::Add(std::set<Item> items) {
    for (auto iter = items.begin(); iter != items.end(); iter++) {
        Add(*iter);
    }
}

bool
StateData::MatchItem(const ItemList& items) {
    for (auto itemIter = items.begin(); itemIter != items.end(); itemIter++) {
        auto match = [&](Item item) -> bool { return *item == **itemIter; };
        auto iter  = std::find_if(_items.begin(), _items.end(), match);
        if (iter == _items.end()) {
            return false;
        }
    }
    return true;
}

int
StateData::GetId() {
    return _id;
}

void
StateData::print() {
    printf(">>>>> state %d start\n", this->_id);
    for (Item item : _items) {
        Rule r = Rules[item->id];
        
        r->print();
        printf("%d", item->dot);
        printf("\n");
    }
    printf("---\n");
    for (Item item : _closures) {
        Rule r = Rules[item->id];

        r->print();
        printf("%d , %d", item->dot, item->next_state);
        printf("\n");
    }
    printf(">>>>> state %d end\n", this->_id);
}

StateCollection::~StateCollection() {
    for (State state : stateList) {
        delete state;
    }
}

int
StateCollection::Size() {
    return stateList.size();
}

bool
StateCollection::IsEmpty(int stateId) {
    return stateList[stateId]->GetItems().size() == 0;
}

void
StateCollection::Add(State state) {
    stateList.push_back(state);
}

void
StateCollection::Add(int stateId, Item item) {
    stateList[stateId]->Add(item);
}

ItemList
StateCollection::GetRules(int stateId) {
    return stateList[stateId]->GetItems();
}

State
StateCollection::GetState(int stateId) {
    return stateList[stateId];
}

State
StateCollection::has(ItemList list) {
    auto j = [](Item l, Item r) {
        if (l->id == r->id) {
            return l->dot < r->dot;
        }
        return l->id < r->id;
    };
  
    std::sort(list.begin(), list.end(), j);
    for (State v : stateList) {
        std::sort(v->_items.begin(), v->_items.end(), j);

        if (list.size() == v->_items.size()) {
            for (int i = 0; i < list.size(); i++) {
                if (list[i]->id == v->_items[i]->id && list[i]->dot == v->_items[i]->dot) {
                    return v;
                }
            }
        }
    }
    return nullptr;
}

int
StateCollection::GetNextId() {
    this->stateId++;
    return this->stateId;
}
