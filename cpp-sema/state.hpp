#ifndef _state_hpp_
#define _state_hpp_

#include "rule.hpp"

class StateData {
private:
    int _id;
    ItemList _items;

public:
    StateData(int id);
    ~StateData();

    ItemList GetItems();

    void ResetItems(ItemList& items);

    void Add(Item item);

    void Add(std::set<Item> item);

    bool MatchItem(const ItemList& items);

    int GetId();
};

typedef StateData* State;
typedef std::vector<State> StateList;

class StateCollection {
    StateList stateList;

public:
    ~StateCollection();
    int Size();
    bool IsEmpty(int stateId);
    void Add(State state);
    void Add(int stateId, Item item);
    ItemList GetRules(int stateId);
    State GetState(int stateId);
};

#endif // !_state_hpp_
