include(`foreach.m4')
define(`_case', `    case $1:
        { $2 }
        break;
')dnl
define(`_cat', `$1$2')dnl
foreach(`x',
`(
`(`0',` ')',
`(`1',` item.node = makeLex(child[0].node, child[1].node, child[2].node, child[3].list, child[5].list, child[7].list, child[8].node, child[10].node ); ')',
`(`2',` item.node = makeParam(child[1].node); ')',
`(`3',` item.node = makeCode(child[1].node); ')',
`(`4',` item.node = makeUnion(child[1].node); ')',
`(`5',` child[0].list->push_back(child[1].node); item.list = child[0].list; ')',
`(`6',` std::vector<Node>* vec = new std::vector<Node>(); vec->push_back(child[0].node); item.list = vec; ')',
`(`7',` item.node = makeToken(child[1].node); ')',
`(`8',` item.node = makeToken(child[2].node, child[4].node); ')',
`(`9',` child[0].list->push_back(child[1].node); item.list = child[0].list; ')',
`(`10',` std::vector<Node>* vec = new std::vector<Node>(); vec->push_back(child[0].node); item.list = vec; ')',
`(`11',` item.node = makeType(child[2].node, child[4].list); ')',
`(`12',` child[0].list->push_back(child[1].node); item.list = child[0].list; ')',
`(`13',` std::vector<Node>* vec = new std::vector<Node>(); vec->push_back(child[0].node); item.list = vec; ')',
`(`14',` item.node = makeRule(child[0].node, child[2].list); ')',
`(`15',` child[0].list->push_back(child[2].node); item.list = child[0].list; ')',
`(`16',` std::vector<Node>* vec = new std::vector<Node>(); vec->push_back(child[0].node); item.list = vec; ')',
`(`17',` item.node = makeRuleRight(child[0].list, child[1].node); ')',
`(`18',` item.node = makeRuleRight(child[0].list, nullptr); ')',
`(`19',` item.node = makeRuleRight(nullptr, child[0].node); ')',
`(`20',` item.node = makeRuleRight(nullptr, nullptr); ')',
`(`21',` child[0].list->push_back(child[1].node); item.list = child[0].list; ')',
`(`22',` std::vector<Node>* vec = new std::vector<Node>(); vec->push_back(child[0].node); item.list = vec; ')',
`(`23',` ')',
`(`24',` ')',
`(`25',` item.node = makeStartRule(child[1].node); ')',
`(`26',`')',
)',
`_cat(`_case', x)')dnl
