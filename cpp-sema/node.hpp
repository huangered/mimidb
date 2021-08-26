#ifndef _sema_node_hpp_
#define _sema_node_hpp_

#include <vector>
#include <string>
#include <map>
#include <algorithm>

using std::string;

class NodeData;

typedef NodeData* Node;

class RuleData;

typedef RuleData* Rule;

class NodeData {
public:
    int _token;
    string _value;

public:
    NodeData();

    virtual ~NodeData();
};

class CodeNode : public NodeData {
public:
    std::string block;
};

class UnionNode : public NodeData {
public:
    std::string block;
};

class ParamNode : public NodeData {
public:
    std::string param;
};

class TypeData : public NodeData {
public:
    string _type;
    std::vector<string> _children;

public:
    void
    SetType(string type) {
        _type = type;
    }
    void
    SetChildren(std::vector<Node>* nodes) {
        std::for_each(nodes->begin(), nodes->end(), [&](Node n) { _children.push_back(n->_value); });
    }
};

class TokenData : public NodeData {
public:
    string _type;
};

class LexNode : public NodeData {
public:
    string unionNode;
    string codeNode;
    string param;
    std::vector<Node>* tokens;
    std::vector<Node>* types;
    std::vector<Node>* rules;
    string other;

public:
    string GetCode();

    string GetUnion();

    std::map<string, string> GetTypeMap();

    std::vector<Rule> GetRules();
};

class RuleNode : public NodeData {
public:
    Node left;
    std::vector<Node>* right;
};

class RuleRightNode : public NodeData {
public:
    std::vector<Node>* right;
    string block;
};

#endif
