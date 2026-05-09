%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

void yyerror(const char *s);
int yylex();

ASTNode* root; /* Global variable to hold the root of the AST */

%}

%union {
    int ival;
    int bval;
    char *sval;
    ASTNode *node;
}

%start program

%token <ival> INTEGER
%token <bval> TRUE FALSE
%token <sval> IDENTIFIER
%token PLUS TIMES LE
%token IF THEN ELSE LET EQUALS IN

%type <node> program expr conditional_expr let_expr rel_expr add_expr mult_expr primary_expr

%nonassoc LE
%left PLUS
%left TIMES

%%

program:
        expr            { root = $1; }
    ;

expr:
        conditional_expr
    ;

conditional_expr:
        IF expr THEN expr ELSE expr
                            { $$ = make_if_node($2, $4, $6); }
    |   let_expr
    |   rel_expr
    ;

let_expr:
        LET IDENTIFIER EQUALS expr IN expr
                            { $$ = make_let_node($2, $4, $6); }
    ;

rel_expr:
        rel_expr LE add_expr
                            { $$ = make_binop_node(LE, $1, $3); }
    |   add_expr
    ;

add_expr:
        add_expr PLUS mult_expr
                            { $$ = make_binop_node(PLUS, $1, $3); }
    |   mult_expr
    ;

mult_expr:
        mult_expr TIMES primary_expr
                            { $$ = make_binop_node(TIMES, $1, $3); }
    |   primary_expr
    ;

primary_expr:
        IDENTIFIER          { $$ = make_id_node($1); }
    |   INTEGER             { $$ = make_int_node($1); }
    |   TRUE                { $$ = make_bool_node(1); }
    |   FALSE               { $$ = make_bool_node(0); }
    ;

%%

/* Error reporting */
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    if (yyparse() == 0) {
        printf("Parsing completed successfully.\n");
        printf("Abstract Syntax Tree:\n");
        print_ast(root);
        printf("\n");
        free_ast(root); /* Free the AST when done */
    }
    return 0;
}
