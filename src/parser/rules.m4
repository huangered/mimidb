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
`(`3',`', `60')',
`(`4',`', `80')',
`(`5',`', `100')',
`(`6',`', `120')',
`(`7',`', `140')',
`(`8',` (item.node) = makeCreateTableStmt((child[2].str), (child[3].list)); ', `160')',
`(`9',` (item.node) = makeSelectStmt((child[3].str), (child[1].list), (child[4].node), (child[5].node)); ', `180')',
`(`10',` ', `200')',
`(`11',` ', `220')',
`(`12',` ', `240')',
`(`13',` (item.list) = (child[1].list);', `260')',
`(`14',` ', `280')',
`(`15',` ', `300')',
`(`16',` ', `320')',
`(`17',` (child[0].list)->push_back((child[2].node)); (item.list) = (child[0].list); ', `340')',
`(`18',` std::vector<Node*>* vec = new std::vector<Node*>(); vec->push_back((child[0].node)); (item.list) = vec; ', `360')',
`(`19',` ', `380')',
`(`20',`', `400')',
`(`21',` ', `420')',
`(`22',` ', `440')',
`(`23',`', `460')',
`(`24',`', `480')',
`(`25',`', `500')',
`(`26',`', `520')',
)',
`_cat(`_case', x)')dnl
