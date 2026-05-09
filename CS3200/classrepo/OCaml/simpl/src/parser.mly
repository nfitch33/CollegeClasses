%{
open Ast
%}

%token <int> INT
%token <string> ID
%token TRUE
%token FALSE
%token LEQ
%token LT
%token GEQ
%token GT
%token TIMES  
%token DIVIDEBY  
%token PLUS
%token MINUS
%token LPAREN
%token RPAREN
%token LET
%token EQUALS
%token IN
%token IF
%token THEN
%token ELSE
%token EOF

%nonassoc IN
%nonassoc ELSE
%left LEQ
%left PLUS MINUS
%left TIMES DIVIDEBY

%start <Ast.expr> prog

%%

prog:
	| e = expr; EOF { e }
	;
	
expr:
	| i = INT { Int i }
	| x = ID { Var x }
	| TRUE { Bool true }
	| FALSE { Bool false }
	| e1 = expr; LEQ; e2 = expr { Binop (Leq, e1, e2) }
	| e1 = expr; TIMES; e2 = expr { Binop (Mult, e1, e2) } 
	| e1 = expr; DIVIDEBY; e2 = expr { Binop (Div, e1, e2) }
	| e1 = expr; PLUS; e2 = expr { Binop (Add, e1, e2) }
	| e1 = expr; MINUS; e2 = expr { Binop (Sub, e1, e2) }
	| LET; x = ID; EQUALS; e1 = expr; IN; e2 = expr { Let (x, e1, e2) }
	| IF; e1 = expr; THEN; e2 = expr; ELSE; e3 = expr { If (e1, e2, e3) }
	| LPAREN; e=expr; RPAREN {e} 
	;

(* The yacc rules without the actions:
expr:
	| e1  LEQ; e2 
	| e1  TIMES; e2 
	| e1  PLUS; e2 
	| LET; x  EQUALS; e1  IN; e2 
*)

(* Corresponding BNF:

e ::= 
	x 
	| i 
	| b 
	| e1 bop e2
    | if e1 then e2 else e3
    | let x = e1 in e2

*)
