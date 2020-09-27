%option never-interactive
%option noyywrap
%option bison-bridge bison-locations

%{
#include "parser.tab.h"
%}

%%
select	    { return SELECT;}
from		{ return FROM; }
[a-zA-Z]*	{ yylval->m = strdup(yytext); return TEXT ;}
\n			{ return EOL; }
";"			{ return EOL; }
"//".*      { /* ignore white space */ }
[\t]		{ /* ignore white space */ }
[ ]			{ /* ignore white space */ }
.			{ printf("Mystery character %c\n", *yytext); }
%%