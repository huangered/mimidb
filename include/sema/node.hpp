#ifndef _sema_node_hpp_
#define _sema_node_hpp_

#include <vector>
#include "lex/lexer.hpp"

class NodeData;

typedef NodeData* Node;

class NodeData {
    std::vector<Node> _nodes;
    const LexToken _token;
    std::string _name;

public:
    NodeData(std::string name);

    NodeData(LexToken token);

    ~NodeData();

    void AddAll(const std::vector<Node>& nodes);
};

#endif