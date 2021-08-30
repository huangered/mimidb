define(CodeBody, `

')
define(UnionBody,`
    Node *node;
')
define(TokenBody, `             CREATE =   2,
              TABLE =   3,
             SELECT =   4,
               FROM =   5,
          semicolon =   6,
')
define(CodeBody2,`
abd;
')
define(NUMNTERM, `2')
define(NUMTOKEN, `7')
define(NUMSTATE, `3')
define(DATA_ACTION, `
{MAX_ID,MAX_ID,1,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-1,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,10000,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
')
define(DATA_GOTO, `
{MAX_ID,2,},
{MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,},
')
define(DATA_RIGHT_NUM, `1,1,')
define(DATA_LEFT_ID, `7,8,')
define(DATA_EOF_ID, `1')
define(DATA_RETURN, ` Node ')
