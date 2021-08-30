include(`foreach.m4')
define(`_case', `    case $1:
        // line $3
        { $2 }
        break;
')dnl
define(`_cat', `$1$2$3')dnl
foreach(`x',
`(
`(`0',` ', `0')',
`(`1',` (item.node) = $1; ', `20')',
)',
`_cat(`_case', x)')dnl
