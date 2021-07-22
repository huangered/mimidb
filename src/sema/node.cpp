#include "sema/node.hpp"

NodeData::NodeData(std::string name)
    : _token{ nullptr }
    , _name{ name } {
}

NodeData::NodeData(LexToken token)
    : _token{ token } {
}

void
NodeData::AddAll(const std::vector<Node>& nodes) {
    _nodes.insert(_nodes.begin(), nodes.begin(), nodes.end());
}