#ifndef _sema_node_hpp_
#define _sema_node_hpp_

#include <vector>
#include "lexer.hpp"

class NodeData;

typedef NodeData* Node;

class NodeData {
    std::vector<Node> _nodes;
    const LexToken _token;
    std::string _name;

public:
    NodeData(std::string name);

    NodeData(LexToken token);

    virtual ~NodeData();

    void AddAll(const std::vector<Node>& nodes);

    std::string Name();

    Node Get(int index);
};

struct TypeData {
    std::string typeName;
    std::vector<std::string> elems;
};

typedef struct TypeData* TypePtr;

struct TokenData {
    std::string name;
};

typedef struct TokenData* TokenPtr;

#endif