%{
#include <stdio.h>
#include <string.h>
%}

LETTER      [a-zA-Z_]
DIGIT       [0-9]
ID          ({LETTER}({LETTER}|{DIGIT})*|{DIGIT}+{LETTER}({LETTER}|{DIGIT})*)
INT         {DIGIT}+
STRING      \"([^\\\"]|\\.)*\"

%%

"buildnode"        { printf("<BUILDNODE>\n"); }
"for"              { printf("<FOR>\n"); }
"in"               { printf("<IN>\n"); }
"print"            { printf("<PRINT>\n"); }

"name"             { printf("<NAME>\n"); }
"weight"           { printf("<WEIGHT>\n"); }
"isachildof"       { printf("<ISACHILDOF>\n"); }

{STRING}           { printf("<STRING, %s>\n", yytext); }
{INT}              { printf("<INT, %s>\n", yytext); }
{ID}               { printf("<ID, %s>\n", yytext); }

"//".*             { /* ignore comments */ }
[ \t\n\r]+         { /* ignore whitespace */ }

    /* symbols */
"+"                { printf("<PLUS>\n"); }
"="                { printf("<ASSIGN>\n"); }
";"                { printf("<SEMICOLON>\n"); }
"{"                { printf("<LBRACE>\n"); }
"}"                { printf("<RBRACE>\n"); }
"("                { printf("<LPAREN>\n"); }
")"                { printf("<RPAREN>\n"); }
"["                { printf("<LBRACKET>\n"); }
"]"                { printf("<RBRACKET>\n"); }
":"                { printf("<COLON>\n"); }
","                { printf("<COMMA>\n"); }

.                  { printf("<ERROR, %s>\n", yytext); }

%%

int main() {
    printf("=== Token Stream Start ===\n\n");
    yylex();
    printf("\n=== Token Stream End ===\n");
    return 0;
}

int yywrap() {
    return 1;
}