%{
#include "tree_builder.tab.h"
#include <cstdlib>
#include <cstring>
%}

%option noyywrap

%%

"PRINT"                     { return PRINT; }

[0-9]+                      {
                                yylval.num = atoi(yytext);
                                return NUMBER;
                            }

[a-zA-Z_][a-zA-Z0-9_]*     {
                                yylval.str = strdup(yytext);
                                return ID;
                            }

"="                         { return '='; }
"["                         { return '['; }
"]"                         { return ']'; }
","                         { return ','; }

[ \t\r\n]+                  ;

.                           {
                                printf("Unknown character: %s\n", yytext);
                            }

%%