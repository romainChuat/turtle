%{
#include <stdio.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
  double value;
  char *name;
  struct ast_node *node;

}

%token <value>    VALUE       "value"
%token <name>     NAME        "name"

%token            KW_FORWARD      "forward"
%token            KW_BACKWARD     "backward"
%token            KW_RIGHT        "right"
%token            KW_LEFT         "left"
%token            KW_POSITION     "position"
%token            KW_UP           "up"
%token            KW_DOWN         "down"
%token            KW_HEADING      "heading"
%token            KW_HOME         "home"
%token            KW_COLOR        "color"
%token            KW_PRINT        "print"

%token            BLOCK_START      "{"
%token            BLOCK_END         "}"

%token            BINOP_PLUS        "+"












/* TODO: add other tokens */

%type <node> unit cmds cmd expr

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_FORWARD expr           { $$ = make_cmd_forward($2); }
  |  KW_BACKWARD expr         { $$ = make_cmd_backward($2); }
  |  KW_RIGHT expr            { $$ = make_cmd_right($2); }
  |  KW_LEFT expr             { $$ = make_cmd_left($2); }
  |  KW_POSITION expr expr    { $$ = make_cmd_position($2, $3); }
  |  KW_UP                    { $$ = make_cmd_up(); }
  |  KW_DOWN                  { $$ = make_cmd_down(); }
  |  KW_HEADING expr          { $$ = make_cmd_heading($2); }
  |  KW_HOME                  { $$ = make_cmd_home(); }
  |  KW_COLOR expr            { $$ = make_cmd_color($2); }
  |  KW_COLOR expr expr expr  { $$ = make_cmd_colorRGB($2,$3,$4); }
  |  KW_PRINT expr            { $$ = make_cmd_print($2); }

  |  BLOCK_START              { $$ = make_block_start();} 
  |  BLOCK_END                { } 

  


;

expr:
    VALUE             { $$ = make_expr_value($1); }
  | NAME              { $$ = make_expr_name($1);}

 // | expr BINOP_PLUS expr       { $$ = make_expr_plus($1,$3);}
  
    /* TODO: add identifier */
;



%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
