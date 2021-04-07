#ifndef _relfilenode_hpp_
#define _relfilenode_hpp_

#include "mimi.hpp"

struct RelFileNode {
	Oid dbNode;
	Oid relNode;

    int hash() const {
        return dbNode * 17 + relNode;
    }

    friend bool operator==(const RelFileNode& l, const RelFileNode& r) {
        return l.dbNode == r.dbNode && l.relNode == r.relNode;
    }

    friend bool operator!=(const RelFileNode& l, const RelFileNode& r) {
        return !(l == r);
    }
};

#endif // !_relfilenode_hpp_
