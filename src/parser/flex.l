%option never-interactive
%option noyywrap
%option bison-bridge bison-locations

%{
#include "parser.tab.h"
%}

%%

create		{ return CREATE; }
table		{ return TABLE; }

primary		{ return PRIMARY; }
key			{ return KEY; }

insert		{ return INSERT; }
into		{ return INTO; }
values		{ return VALUES; }
select	    { return SELECT; }
from		{ return FROM; }
where		{ return WHERE; }
and			{ return AND; }
update		{ return UPDATE; }
set			{ return SET; }
=			{ return EQ; }
[(),]       { return yytext[0]; }

'[a-z0-9]*'	{ yylval->str = strdup(yytext); return TEXT; }
[a-z][a-z0-9]*	{ yylval->str = strdup(yytext); return IDENT; }
[0-9]+		{ yylval->integer = atoi(yytext); return INTEGER; }

\n			{ return EOL; }
";"			{ return EOL; }
"//".*      { /* ignore white space */ }
[\t]		{ /* ignore white space */ }
[ ]			{ /* ignore white space */ }
.			{ printf("Mystery character %c\n", *yytext); }
%%