%code requires {
    #include <vector>
    #include <string>
    #include "tree_node.h"
}

%{
#include <iostream>
#include <vector>
#include <cstring>
#include "parse_tree.h"

int yylex();
void yyerror(const char *s);

ParseTree pt;
%}

%union {
    char* str;
    int num;
    TreeNode* node;
    std::vector<TreeNode*>* vec;
}

%token <str> ID
%token <num> NUMBER
%token PRINT

%type <node> tree
%type <vec> list

%start program

%%

program:
    statements
;

statements:
      statements statement
    | statement
;

statement:
      ID '=' tree
      {
          pt.assign($1, $3);
      }
    | PRINT ID
      {
          pt.print($2);
      }
    | error
      {
          yyerrok;
      }
;

tree:
      ID NUMBER
      {
          $$ = new TreeNode($1, $2);
      }
    | ID NUMBER '[' list ']'
      {
          $$ = new TreeNode($1, $2);

          for (auto c : *$4)
              $$->addChild(c);

          delete $4;
      }
;

list:
      tree
      {
          $$ = new std::vector<TreeNode*>();
          $$->push_back($1);
      }
    | list ',' tree
      {
          $1->push_back($3);
          $$ = $1;
      }
;

%%

void yyerror(const char *s) {
    std::cerr << "Parse error: " << s << std::endl;
}

int main() {
    return yyparse();
}