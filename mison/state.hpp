#ifndef _state_hpp_
#define _state_hpp_

#include "rule.hpp"

class StateData {
public:
    int _id;
    ItemList _items;
    ItemList _closures;

public:
    StateData(int id);
    ~StateData();

    ItemList GetItems();

    void ResetItems(ItemList& items);

    void Add(Item item);

    void Add(std::set<Item> item);

    bool MatchItem(const ItemList& items);

    int GetId();

    void print();
};

typedef StateData* State;
typedef std::vector<State> StateList;

class StateCollection {
    int stateId;
    StateList stateList;

public:
    ~StateCollection();
    int Size();
    bool IsEmpty(int stateId);
    void Add(State state);
    void Add(int stateId, Item item);
    ItemList GetRules(int stateId);
    State GetState(int stateId);

    State has(ItemList list);

    int GetNextId();
};

#endif // !_state_hpp_
