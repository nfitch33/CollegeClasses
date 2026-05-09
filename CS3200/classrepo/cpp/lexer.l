%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "y.tab.h"
%}

digit       [0-9]
letter      [a-zA-Z]
identifier  {letter}({letter}|{digit})*

%%

"+"             { return PLUS; }
"*"             { return TIMES; }
"<="            { return LE; }
"if"            { return IF; }
"then"          { return THEN; }
"else"          { return ELSE; }
"let"           { return LET; }
"="             { return EQUALS; }
"in"            { return IN; }
"true"          { return TRUE; }
"false"         { return FALSE; }
{digit}+        { yylval.ival = atoi(yytext); return INTEGER; }
{identifier}    { yylval.sval = strdup(yytext); return IDENTIFIER; }
[ \t\n]+        { /* skip whitespace */ }
.               { printf("Unrecognized character: %s\n", yytext); }

%%

int yywrap() { return 1; }
