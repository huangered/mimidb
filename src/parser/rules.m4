include(`foreach.m4')
define(`_case', `    case $1:
        // line $3
        { $2 }
        break;
')dnl
define(`_cat', `$1$2$3')dnl
foreach(`x',
`(
`(`0',` (item.node) = (child[0].node) ; ', `0')',
`(`1',` ', `20')',
`(`2',` ', `40')',
`(`3',` (item.node) = (child[0].node); ', `60')',
`(`4',` (item.node) = (child[0].node); ', `80')',
`(`5',` (item.node) = (child[0].node); ', `100')',
`(`6',` (item.node) = (child[0].node); ', `120')',
`(`7',` (item.node) = (child[0].node); ', `140')',
`(`8',` (item.node) = makeCreateTableStmt((child[2].str), (child[3].list)); ', `160')',
`(`9',` (item.node) = makeSelectStmt((child[3].str), (child[1].list), (child[4].node), (child[5].node)); ', `180')',
`(`10',` (item.node) = makeUpdateStmt((child[1].str), (child[3].list), (child[4].node)); ', `200')',
`(`11',` (item.node) = makeInsertStmt((child[2].str), (child[4].list)); ', `220')',
`(`12',` ', `240')',
`(`13',` (item.list) = (child[1].list);', `260')',
`(`14',` (child[0].list)->push_back((child[2].node)); (item.list) = (child[0].list);  ', `280')',
`(`15',` std::vector<Node*>* vec = new std::vector<Node*>(); vec->push_back((child[0].node)); (item.list) = vec; ', `300')',
`(`16',` (item.node) = makeColumnDef((child[0].str), (child[1].str)); ', `320')',
`(`17',` (child[0].list)->push_back((child[2].node)); (item.list) = (child[0].list); ', `340')',
`(`18',` std::vector<Node*>* vec = new std::vector<Node*>(); vec->push_back((child[0].node)); (item.list) = vec; ', `360')',
`(`19',` (item.node) = makeStrValue((child[0].str)); ', `380')',
`(`20',`', `400')',
`(`21',` (item.node) = makeWhereStmt((child[1].list)); ', `420')',
`(`22',` (child[0].list)->push_back((child[1].node)); (item.list) = (child[0].list); ', `440')',
`(`23',`  std::vector<Node*>* vec = new std::vector<Node*>(); vec->push_back((child[0].node)); (item.list) = vec;  ', `460')',
`(`24',`', `480')',
`(`25',` (item.node) = makeOrderbyStmt((child[1].list)); ', `500')',
`(`26',` (child[0].list)->push_back((child[2].node)); (item.list) = (child[0].list); ', `520')',
`(`27',` std::vector<Node*>* vec = new std::vector<Node*>(); vec->push_back((child[0].node)); (item.list) = vec;  ', `540')',
`(`28',` (item.list) = (child[1].list); ', `560')',
`(`29',` (child[0].list)->push_back((child[2].node)); (item.list) = (child[0].list); ', `580')',
`(`30',` std::vector<Node*>* vec = new std::vector<Node*>(); vec->push_back((child[0].node)); (item.list) = vec;  ', `600')',
`(`31',` (item.node) = makeStrValue((child[0].str)); ', `620')',
`(`32',` (item.node) = makeIntValue((child[0].num)); ', `640')',
`(`33',`  (child[0].list)->push_back((child[2].node)); (item.list) = (child[0].list);  ', `660')',
`(`34',` std::vector<Node*>* vec = new std::vector<Node*>(); vec->push_back((child[0].node)); (item.list) = vec; ', `680')',
`(`35',` (item.node) = makeSetParam((child[0].str), (child[2].node)); ', `700')',
`(`36',` (item.node) = makeSetParam((child[0].str), (child[2].node)); ', `720')',
`(`37',`', `740')',
)',
`_cat(`_case', x)')dnl
