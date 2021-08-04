#ifndef _gogo_hpp_
#define _gogo_hpp_
#include "sema/node.hpp"

inline Node
gogo(Node n0) {
    Node n = new NodeData{ "a" };
    n->AddAll({ n0 });
    return n;
}

inline Node
gogo(Node n0, Node n1) {
    Node n = new NodeData{ "a" };
    n->AddAll({ n0, n1 });
    return n;
}

inline Node
gogo(Node n0, Node n1, Node n2) {
    Node n = new NodeData{ "a" };
    n->AddAll({ n0, n1, n2 });
    return n;
}

inline Node
gogo(Node n0, Node n1, Node n2, Node n3) {
    Node n = new NodeData{ "a" };
    n->AddAll({ n0, n1, n2, n3 });
    return n;
}

inline Node
gogo(Node n0, Node n1, Node n2, Node n3, Node n4) {
    Node n = new NodeData{ "a" };
    n->AddAll({ n0, n1, n2, n3, n4 });
    return n;
}

inline Node
gogo(Node n0, Node n1, Node n2, Node n3, Node n4, Node n5) {
    Node n = new NodeData{ "a" };
    n->AddAll({ n0, n1, n2, n3, n4, n5 });
    return n;
}

inline Node
gogo(Node n0, Node n1, Node n2, Node n3, Node n4, Node n5, Node n6) {
    Node n = new NodeData{ "a" };
    n->AddAll({ n0, n1, n2, n3, n4, n5, n6 });
    return n;
}

inline Node
gogo(Node n0, Node n1, Node n2, Node n3, Node n4, Node n5, Node n6, Node n7) {
    Node n = new NodeData{ "a" };
    n->AddAll({ n0, n1, n2, n3, n4, n5, n6, n7 });
    return n;
}

class SelectStmtNodeData : public NodeData {
public:
    using NodeData::NodeData;
};

typedef SelectStmtNodeData* SelectStmtNode;

inline SelectStmtNode
makeSelectStmt(Node params, Node tableName, Node whereStmt, Node orderByStmt) {
    SelectStmtNode node = new SelectStmtNodeData{ "select stmt" };
    node->AddAll({ params, tableName, whereStmt, orderByStmt });
    return node;
}

#endif