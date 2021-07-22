#include "sema/node.hpp"

NodeData::NodeData()
    : _token{ nullptr } {
}

NodeData::NodeData(LexToken token)
    : _token{ token } {
}

void
NodeData::AddAll(const std::vector<Node>& nodes) {
    _nodes.insert(_nodes.begin(), nodes.begin(), nodes.end());
}