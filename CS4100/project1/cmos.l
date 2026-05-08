%{
#include <stdio.h>
#include <string.h>

FILE *out;

void emit_token(const char *token) {
    fprintf(out, "%s", token);
}
%}

ID      [a-zA-Z_][a-zA-Z0-9_]*
NUMBER  [0-9]+

%%

[ \t\n]+               { /* skip whitespace */ }


"//".*                      { /* skip line comments */ }

"if"        { emit_token("001"); }
"else"      { emit_token("002"); }
"for"       { emit_token("003"); }
"while"     { emit_token("004"); }
"return"    { emit_token("005"); }
"int"       { emit_token("006"); }
"float"     { emit_token("007"); }
"double"    { emit_token("008"); }
"char"      { emit_token("009"); }
"void"      { emit_token("010"); }

"=="        { emit_token("100"); }
"!="        { emit_token("101"); }
"<="        { emit_token("102"); }
">="        { emit_token("103"); }
"++"        { emit_token("112"); }
"--"        { emit_token("113"); }
"+="        { emit_token("114"); }
"-="        { emit_token("115"); }
"*="        { emit_token("116"); }
"/="        { emit_token("117"); }

"="         { emit_token("104"); }
"<"         { emit_token("105"); }
">"         { emit_token("106"); }
"+"         { emit_token("107"); }
"-"         { emit_token("108"); }
"*"         { emit_token("109"); }
"/"         { emit_token("110"); }
"%"         { emit_token("111"); }

";"         { emit_token("118"); }
","         { emit_token("119"); }
"("         { emit_token("120"); }
")"         { emit_token("121"); }
"{"         { emit_token("122"); }
"}"         { emit_token("123"); }

{NUMBER}    { emit_token("200"); }
{ID}        { emit_token("201"); }

.           { /* skip everything else */ }

%%

int main(int argc, char **argv) {
    out = fopen("scanner_out.txt", "w");
    if (!out) { perror("scanner_out.txt"); return 1; }
    yylex();
    fclose(out);
    return 0;
}