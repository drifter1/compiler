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

/* token definition */
%token CHAR INT FLOAT DOUBLE IF ELSE WHILE FOR CONTINUE BREAK VOID RETURN
%token ADDOP MULOP DIVOP INCR OROP ANDOP NOTOP EQUOP RELOP
%token LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE SEMI DOT COMMA ASSIGN REFER
%token ID ICONST FCONST CCONST STRING

%start program

/* expression priorities and rules */

%%

program: declarations statements ;

declarations: declarations declaration | declaration;

declaration: type names SEMI ;

type: INT | CHAR | FLOAT | DOUBLE | VOID;

names: variable | names COMMA variable;

variable: ID |
    pointer ID |
    ID array
;

pointer: pointer MULOP | MULOP ;

array: array LBRACK ICONST RBRACK | LBRACK ICONST RBRACK ;

statements: statements statement | statement;

statement:
	if_statement | for_statement | while_statement | assigment |
	CONTINUE SEMI | BREAK SEMI | RETURN SEMI
;

if_statement: IF LPAREN expression RPAREN tail else_if_part else_part ;

else_if_part: 
	else_if_part ELSE IF LPAREN expression RPAREN tail |
	ELSE IF LPAREN expression RPAREN tail  |
	/* empty */
; 
else_part: ELSE tail | /* empty */ ; 

for_statement: FOR LPAREN expression SEMI expression SEMI expression RPAREN tail ;

while_statement: WHILE LPAREN expression RPAREN tail ;

tail: statement SEMI | LBRACE statements RBRACE ;

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
    sign constant
;

sign: ADDOP | /* empty */ ; 

constant: ICONST | FCONST | CCONST ;

assigment: reference variable ASSIGN expression SEMI ; 

reference: REFER | /* empty */ ;

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
