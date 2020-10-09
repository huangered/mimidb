%code requires {
#include "parser/tokens.h"
#include "node/parsenode.h"
}
/* simplest version of calculator */
%code {
#include <stdio.h>

void yyerror(YYLTYPE* a, void* b, const char* s);

}

%locations
%pure_parser
%parse-param {NodeWrap* yyscanner}
%lex-param   {NodeWrap* yyscanner}

%union {
    Node *node;
    char* str;
	List* list;
}

/* declare tokens */
%token EOL
%token INSERT
%token INTO
%token VALUES
%token SELECT
%token FROM
%token TEXT
%type <str> term
%type <str> tbl_name
%type <list> value_list
%type <list> term_list
%type <node> stmt InsertStmt SelectStmt
%%

stmt: /* nothing */
  InsertStmt
  | SelectStmt
  ;
SelectStmt:
  SELECT value_list FROM tbl_name EOL { yyscanner->node = makeSelectStmt($4, $2); }
  ;
InsertStmt:
  INSERT INTO tbl_name VALUES value_list EOL { yyscanner->node = makeInsertStmt($3, $5); }
  ;
tbl_name:
  term { $$ = $1; };

value_list:
  '(' term_list ')' { $$ = $2; }
  ;

term_list: 
   term { $$ = new_list($1, 100) ; }
  | term_list ',' term { $$ = append_list($1, $3); }
  ;
term: TEXT {}
  ;
%start stmt;
%%

Node*
raw_parse(const char* str)
{
  // note yy_scan_buffer is is looking for a double null string
  yy_scan_string(str);
  NodeWrap p;

  int i = yyparse(&p);
  if(i == 0) {
    return p.node;
  }
  return NULL;
}

void
yyerror(YYLTYPE* a, void* b, const char *s)
{
    printf("error: %s\n", s);
}

Node*
makeSelectStmt(char* tbl_name, List* a2) {
	printf("makeSelectStmt\n");
	SelectStmt* stmt = (SelectStmt*)malloc(sizeof(SelectStmt));
	stmt->nodetag = NT_SelectStmt;
	stmt->relname = tbl_name;
	stmt->column = a2;
	return (Node*)stmt;
}

Node*
makeInsertStmt(char* tbl_name, List* a2) {
	printf("makeInsertStmt\n");
	InsertStmt* stmt = (InsertStmt*)malloc(sizeof(InsertStmt));
	stmt->nodetag = NT_InsertStmt;
	stmt->relname = tbl_name;
	stmt->column = a2;
	return (Node*)stmt;
}
