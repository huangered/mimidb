#ifndef _sema_node_hpp_
#define _sema_node_hpp_

#include <vector>
#include "lexer.hpp"

class NodeData;

typedef NodeData* Node;

class NodeData {
    LexToken _token;
    std::string _name;

public:
    NodeData();

    virtual ~NodeData();

    std::string Name();
    void SetToken(LexToken token);
};

class TypeData : public NodeData {};

class TokenData : public NodeData {};

class LexNode : public NodeData {
public:
    std::vector<Node>* tokens;
    std::vector<Node>* types;
    std::vector<Node>* rules;
};

class RuleNode : public NodeData {
public:
    Node left;
    std::vector<Node>* right;
    Node block;
};

#endif