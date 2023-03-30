%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]
FLOAT []


%%

{DIGIT}+            { yylval.value = strtod(yytext, NULL); return VALUE; }
"forward"           { return KW_FORWARD; }
"backward"          { return KW_BACKWARD; }
"right"             { return KW_RIGHT; }
"left"              { return KW_LEFT; }
"position"          { return KW_POSITION; }
"up"                { return KW_UP; }
"down"              { return KW_DOWN; }
"heading"           { return KW_HEADING; }
"home"              { return KW_HOME; }
"color"             { return KW_COLOR; }
"print"             { return KW_PRINT; }
"{"                 {return BLOCK_START;}
"}"                 {return BLOCK_END;}






[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
