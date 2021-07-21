#include "sema/node.hpp"

NodeData::NodeData() : _token{ nullptr } {
}

NodeData::NodeData(LexToken token) : _token{ token } {
}

void
NodeData::AddAll(std::vector<Node> nodes) {
    for (Node n : nodes) {
        _nodes.push_back(n);
    }
}