%{
	#include "symtab.c"
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	extern FILE *yyin;
	extern FILE *yyout;
	extern int lineno;
	extern int yylex();
	void yyerror();
%}

/* YYSTYPE union */
%union{
    char char_val;
	int int_val;
	double double_val;
	char* str_val;
	list_t* symtab_item;
}

/* token definition */
%token<int_val> CHAR INT FLOAT DOUBLE IF ELSE WHILE FOR CONTINUE BREAK VOID RETURN
%token<int_val> ADDOP MULOP DIVOP INCR OROP ANDOP NOTOP EQUOP RELOP
%token<int_val> LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE SEMI DOT COMMA ASSIGN REFER
%token <symtab_item> ID
%token <int_val> 	 ICONST
%token <double_val>  FCONST
%token <char_val> 	 CCONST
%token <str_val>     STRING

%start program

/* expression priorities and rules */

%%

program: declarations statements RETURN SEMI functions;

functions: functions function | function;

function: function_head function_tail | /* empty */ ;
		
function_head: return_type ID LPAREN param_empty RPAREN;

function_tail: LBRACE declarations statements RBRACE;

param_empty: parameters | /* empty */;

return_type: pointer type | pointer;

parameters: parameters COMMA parameter | parameter;

parameter : type variable;

declarations: declarations declaration | declaration;

declaration: type names SEMI ;

type: INT | CHAR | FLOAT | DOUBLE | VOID;

names: variable init | names COMMA variable init;

variable: ID |
    pointer ID |
    ID array
;

init: ASSIGN init_value | /* empty */ ;

init_value: constant | array_init ;

array_init: LBRACE values RBRACE ;

values: values COMMA constant | constant ;

pointer: pointer MULOP | MULOP ;

array: array LBRACK expression RBRACK | LBRACK expression RBRACK ;

statements: statements statement | statement ;

statement:
	if_statement | for_statement | while_statement | assigment |
	CONTINUE SEMI | BREAK SEMI | function_call SEMI
;

if_statement: IF LPAREN expression RPAREN tail else_if_part else_part ;

else_if_part: 
	else_if_part ELSE IF LPAREN expression RPAREN tail |
	ELSE IF LPAREN expression RPAREN tail  |
	/* empty */
; 
else_part: ELSE tail | /* empty */ ; 

for_statement: FOR LPAREN assigment expression SEMI expression RPAREN tail ;

while_statement: WHILE LPAREN expression RPAREN tail ;

tail: LBRACE statements RBRACE ;

expression:
    expression ADDOP expression |
    expression MULOP expression |
    expression DIVOP expression |
    expression INCR |
    INCR expression |
    expression OROP expression |
    expression ANDOP expression |
    NOTOP expression |
    expression EQUOP expression |
    expression RELOP expression |
    LPAREN expression RPAREN |
    variable |
    sign constant |
	function_call
;

sign: ADDOP | /* empty */ ; 

constant: ICONST | FCONST | CCONST ;

assigment: reference variable ASSIGN expression SEMI ; 

reference: REFER | /* empty */ ;

function_call: ID LPAREN call_params RPAREN;

call_params: call_param | STRING | /* empty */

call_param : call_param COMMA variable | variable ;

%%
void yyerror ()
{
  fprintf(stderr, "Syntax error at line %d\n", lineno);
  exit(1);
}
int main (int argc, char *argv[]){
	// initialize symbol table
	init_hash_table();
	// parsing
	int flag;
	yyin = fopen(argv[1], "r");
	flag = yyparse();
	fclose(yyin);
	
	// symbol table dump
	yyout = fopen("symtab_dump.out", "w");
	symtab_dump(yyout);
	fclose(yyout);	
	
	return flag;
}
