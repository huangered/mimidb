#ifndef _relfilenode_hpp_
#define _relfilenode_hpp_

#include "mimi.hpp"

struct RelFileNode {
	Oid dbNode;
	Oid relNode;
};

#endif // !_relfilenode_hpp_
