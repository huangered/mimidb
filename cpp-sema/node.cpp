#include "node.hpp"

NodeData::NodeData(std::string name)
    : _token{ nullptr }
    , _name{ name } {
}

NodeData::NodeData(LexToken token)
    : _token{ token } {
}

NodeData::~NodeData() {
    if (_token != nullptr) {
        delete _token;
    }
    for (Node n : _nodes) {
        delete n;
    }
}

void
NodeData::AddAll(const std::vector<Node>& nodes) {
    _nodes.insert(_nodes.begin(), nodes.begin(), nodes.end());
}

std::string
NodeData::Name() {
    return _name;
}

Node
NodeData::Get(int index) {
    return this->_nodes[index];
}
