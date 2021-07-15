#ifndef _sema_node_hpp_
#define _sema_node_hpp_

#include <vector>

class SemaTokenData;
class NodeData;

typedef SemaTokenData* SemaToken;
typedef NodeData* Node;

class NodeData {
    std::vector<Node> _nodes;
    const SemaToken _token;

public:
    NodeData(SemaToken token) : _token{token} {
    }

    void
    addAll(std::vector<Node> nodes) {
        for (Node n : nodes) {
            _nodes.push_back(n);
        }
    }

    SemaToken
    getToken() {
        return _token;
    }
};

#endif