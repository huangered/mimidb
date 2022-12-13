include(`foreach.m4')
define(`_case', `    case $1:
        // line $3
        { $2 }
        break;
')dnl
define(`_cat', `$1$2$3')dnl
foreach(`x',
`(
`(`0',` (item.node) = makeLex((child[0].node), (child[1].node), (child[2].node), (child[3].list), (child[5].list), (child[7].list), (child[8].str), (child[10].node) ); ', `0')',
`(`1',` (item.node) = makeParam((child[1].node)); ', `20')',
`(`2',` (item.node) = makeCode((child[1].node)); ', `40')',
`(`3',` (item.node) = makeUnion((child[1].node)); ', `60')',
`(`4',` (child[0].list)->push_back((child[1].node)); (item.list) = (child[0].list); ', `80')',
`(`5',` std::vector<Node>* vec = new std::vector<Node>(); vec->push_back((child[0].node)); (item.list) = vec; ', `100')',
`(`6',` (item.node) = makeToken((child[1].node)); ', `120')',
`(`7',` (item.node) = makeToken((child[2].node), (child[4].node)); ', `140')',
`(`8',` (child[0].list)->push_back((child[1].node)); (item.list) = (child[0].list); ', `160')',
`(`9',` std::vector<Node>* vec = new std::vector<Node>(); vec->push_back((child[0].node)); (item.list) = vec; ', `180')',
`(`10',` (item.node) = makeType((child[2].node), (child[4].list)); ', `200')',
`(`11',` (child[0].list)->push_back((child[1].node)); (item.list) = (child[0].list); ', `220')',
`(`12',` std::vector<Node>* vec = new std::vector<Node>(); vec->push_back((child[0].node)); (item.list) = vec; ', `240')',
`(`13',` (item.node) = makeRule((child[0].node), (child[2].list)); ', `260')',
`(`14',` (child[0].list)->push_back((child[2].node)); (item.list) = (child[0].list); ', `280')',
`(`15',` std::vector<Node>* vec = new std::vector<Node>(); vec->push_back((child[0].node)); (item.list) = vec; ', `300')',
`(`16',` (item.node) = makeRuleRight((child[0].list), (child[1].node)); ', `320')',
`(`17',` (item.node) = makeRuleRight((child[0].list), NULL); ', `340')',
`(`18',` (item.node) = makeRuleRight(NULL, (child[0].node)); ', `360')',
`(`19',` (item.node) = makeRuleRight(NULL, NULL); ', `380')',
`(`20',` (child[0].list)->push_back((child[1].node)); (item.list) = (child[0].list); ', `400')',
`(`21',` std::vector<Node>* vec = new std::vector<Node>(); vec->push_back((child[0].node)); (item.list) = vec; ', `420')',
`(`22',` (item.node) = (child[0].node) ; ', `440')',
`(`23',` (item.node) = (child[0].node); ', `460')',
`(`24',` (item.str) = makeStartRule((child[1].node)); ', `480')',
`(`25',`', `500')',
`(`26',`', `520')',
)',
`_cat(`_case', x)')dnl
