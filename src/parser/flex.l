%option never-interactive
%option noyywrap
%option bison-bridge bison-locations

%{
#include "parser.tab.h"
%}

%%
select	    { printf("1\n"); return SELECT;}
from		{ printf("2\n"); return FROM; }
[a-zA-Z]*	{ printf("3\n"); yylval->m = strdup(yytext); return TEXT ;}
\n			{ printf("4\n"); return EOL; }
";"			{ printf("5\n"); return EOL; }
"//".*      { printf("6\n"); }
[\t]		{ printf("7\n"); /* ignore white space */ }
[ ]			{ printf("8\n"); /* ignore white space */ }
.			{ printf("Mystery character %c\n", *yytext); }
%%