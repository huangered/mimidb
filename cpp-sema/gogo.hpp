#ifndef _gogo_hpp_
#define _gogo_hpp_
#include "sema/node.hpp"
#include <vector>

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

    Node params;
    Node tableName;
    Node whereStmt;

    ~SelectStmtNodeData() {
        delete params;
        delete tableName;
        if (whereStmt != nullptr) {
            delete whereStmt;
        }
    }
};

typedef SelectStmtNodeData* SelectStmtNode;

inline SelectStmtNode
makeSelectStmt(Node params, Node tableName, Node whereStmt) {
    SelectStmtNode node = new SelectStmtNodeData{ "select stmt" };
    node->params        = params;
    node->tableName     = tableName;
    node->whereStmt     = whereStmt;
    return node;
}

class StarNodeData : public NodeData {
public:
    using NodeData::NodeData;
};

typedef StarNodeData* StarNode;

inline Node
makeStarStmt(Node n0) {
    StarNode node = new StarNodeData{ "star" };
    return node;
}

inline Node
makeBlock(std::vector<Node>* vec) {
    Node node = new NodeData("block");
    node->AddAll(*vec);
    delete vec;
    return node;
}

#endif