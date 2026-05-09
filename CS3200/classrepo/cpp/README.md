# C and C++
## Parser implementation in C using Yacc and Lex (or [Bison and Flex](https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html))

![image](https://github.com/user-attachments/assets/5bb6793f-7c2d-4b88-a0dc-9f0f7fffd022)


To implement a parser for a simple language using Lex and Yacc, we can create two files:

* Lexer (lex file): This file will tokenize the input string into meaningful symbols.
* Parser (yacc file): This file will parse the tokens according to the grammar rules and build an Abstract Syntax Tree (AST).

Example:
### Lexer (lexer.l):
```lex
%{
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
```

### Parser (parser.y):
```yacc
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex();

typedef struct ASTNode {
    enum { NODE_INT, NODE_BOOL, NODE_ID, NODE_BINOP, NODE_IF, NODE_LET } nodetype;
    union {
        int ival;
        int bval;
        char *sval;
        struct {
            struct ASTNode *left;
            int op; // e.g., PLUS, TIMES, LE
            struct ASTNode *right;
        } binop;
        struct {
            struct ASTNode *cond;
            struct ASTNode *then_branch;
            struct ASTNode *else_branch;
        } ifnode;
        struct {
            char *id;
            struct ASTNode *expr1;
            struct ASTNode *expr2;
        } letnode;
    } data;
} ASTNode;

ASTNode* make_int_node(int value);
ASTNode* make_bool_node(int value);
ASTNode* make_id_node(char* id);
ASTNode* make_binop_node(int op, ASTNode* left, ASTNode* right);
ASTNode* make_if_node(ASTNode* cond, ASTNode* then_branch, ASTNode* else_branch);
ASTNode* make_let_node(char* id, ASTNode* expr1, ASTNode* expr2);

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
        expr { /* AST root is in $$ */ }
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

/* Helper functions to create AST nodes */
ASTNode* make_int_node(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->nodetype = NODE_INT;
    node->data.ival = value;
    return node;
}

ASTNode* make_bool_node(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->nodetype = NODE_BOOL;
    node->data.bval = value;
    return node;
}

ASTNode* make_id_node(char* id) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->nodetype = NODE_ID;
    node->data.sval = strdup(id);
    return node;
}

ASTNode* make_binop_node(int op, ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->nodetype = NODE_BINOP;
    node->data.binop.op = op;
    node->data.binop.left = left;
    node->data.binop.right = right;
    return node;
}

ASTNode* make_if_node(ASTNode* cond, ASTNode* then_branch, ASTNode* else_branch) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->nodetype = NODE_IF;
    node->data.ifnode.cond = cond;
    node->data.ifnode.then_branch = then_branch;
    node->data.ifnode.else_branch = else_branch;
    return node;
}

ASTNode* make_let_node(char* id, ASTNode* expr1, ASTNode* expr2) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->nodetype = NODE_LET;
    node->data.letnode.id = strdup(id);
    node->data.letnode.expr1 = expr1;
    node->data.letnode.expr2 = expr2;
    return node;
}

/* Error reporting */
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    yyparse();
    printf("Parsing completed successfully.\n");
    return 0;
}

```
### To run and test this parser:
```console
sudo apt-get install bison flex
yacc -d parser.y
lex lexer.l
gcc y.tab.c lex.yy.c -o parser
./parser
```

One can test the parser with expressions like:

```
let x = 3 + 4 in if x <= 7 then true else false
if true then 1 else 0
x * y + z
```

### To run and test the parser in this folder
(Printing of AST is still incomplete)
```console
./build.sh
# Or: gcc y.tab.c lex.yy.c ast.c -o parser
```
Type `^d` to end the input stream.
```console
@drchangliu ➜ /workspaces/cs3200/cpp (main) $ ./parser
5+5
Parsing completed successfully.
Abstract Syntax Tree:
@drchangliu ➜ /workspaces/cs3200/cpp (main) $ ./parser
6+6*3
Parsing completed successfully.
Abstract Syntax Tree:
@drchangliu ➜ /workspaces/cs3200/cpp (main) $ 
```
