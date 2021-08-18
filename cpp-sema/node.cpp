#include "node.hpp"

NodeData::NodeData() {
}

NodeData::~NodeData() {
    if (_token != nullptr) {
        delete _token;
    }
}

std::string
NodeData::Name() {
    return _name;
}

void
NodeData::SetToken(LexToken token) {
    _token = token;
}