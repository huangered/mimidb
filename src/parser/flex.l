%option never-interactive
%option noyywrap
%option bison-bridge bison-locations

%{
#include "parser.tab.h"
%}

%%

create		{ return CREATE; }
table		{ return TABLE; }

insert		{ return INSERT; }
into		{ return INTO; }
values		{ return VALUES; }
select	    { return SELECT; }
from		{ return FROM; }
update		{ return UPDATE; }
set			{ return SET; }
[(),]       { return yytext[0]; }
[a-zA-Z]*	{ yylval->str = strdup(yytext); return TEXT ;}
\n			{ return EOL; }
";"			{ return EOL; }
"//".*      { /* ignore white space */ }
[\t]		{ /* ignore white space */ }
[ ]			{ /* ignore white space */ }
.			{ printf("Mystery character %c\n", *yytext); }
%%