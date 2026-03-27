%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "../include/compiler.h"
%}

/* YYSTYPE union */
%union{
	// different types of values
    char *sval;
	value val;

	// data type
	data_type d_type;

	// operator type
	operator_type op_type;

    // structures
	symtab_entry *symtab_entry;
    ast_node *ast_node;
	list_node *list_node;
}

/* token (terminal) definition */
%token 					T_BREAK				"break"
%token 					T_CHAR				"char"
%token					T_CONTINUE			"continue"
%token					T_DOUBLE			"double"
%token					T_ELSE				"else"
%token					T_FLOAT				"float"
%token					T_FOR				"for"
%token					T_IF				"if"
%token					T_INT				"int"
%token					T_RETURN			"return"
%token					T_VOID				"void"
%token 					T_WHILE				"while"
%token					T_INPUT				"input"
%token					T_MAIN				"main"
%token					T_PRINT				"print"
%token <op_type>		T_ASSIGN			"="
%token <op_type>		T_INCDEC			"++ or --"
%token <op_type>		T_ADDOP				"+ or -"
%token <op_type>		T_MULOP				"* or / or %"
%token <op_type> 		T_OROP				"||"
%token <op_type>		T_ANDOP				"&&"
%token <op_type>		T_NOTOP				"!"
%token <op_type>		T_EQUOP				"== or !="
%token <op_type>		T_RELOP				"> or < or >= or <="
%token 					T_LPAREN			"("
%token 					T_RPAREN			")"
%token 					T_LBRACE			"{"
%token 					T_RBRACE			"}"
%token 					T_COMMA				","
%token 					T_SEMI				";"
%token <sval>			T_ID				"identifier"
%token <val> 			T_ICONST			"unsigned integer constant"
%token <val> 			T_FCONST			"unsigned floating-point constant"
%token <val> 			T_CCONST			"character constant"
%token <sval> 			T_STRING			"string"

/* precedencies and associativities */
%left 	T_COMMA
%right 	T_ASSIGN
%left 	T_OROP
%left 	T_ANDOP
%left 	T_EQUOP
%left 	T_RELOP
%left 	T_ADDOP
%left 	T_MULOP
%right 	T_NOTOP		INCDEC_PREFIX		UNARY_PLUS_MINUS
%left	T_LPAREN	T_RPAREN			INCDEC_POSTFIX

/* rule (non-terminal) definitions */
%type <ast_node> 		program
%type <list_node> 		declarations
%type <ast_node> 		declaration
%type <d_type>	 		basic_type
%type <list_node> 		names
%type <symtab_entry>	var_init
%type <symtab_entry> 	variable
%type <val> 			init
%type <ast_node>		constant
%type <list_node> 		functions
%type <ast_node> 		function
%type <symtab_entry> 	function_head
%type <symtab_entry> 	function_head_start
%type <list_node> 		parameters
%type <symtab_entry> 	parameter
%type <ast_node> 		function_tail 
%type <list_node> 		statements
%type <ast_node> 		statement
%type <ast_node> 		if_statement
%type <ast_node> 		expression
%type <ast_node> 		var_ref
%type <ast_node> 		function_call
%type <list_node> 		arguments
%type <ast_node>		argument
%type <list_node> 		tail
%type <list_node> 		else_if
%type <list_node> 		optional_else
%type <ast_node> 		for_loop
%type <ast_node> 		assigment
%type <ast_node> 		while_loop
%type <ast_node> 		print_statement
%type <ast_node> 		input_statement
%type <ast_node> 		return_statement
%type <ast_node> 		main_function
%type <symtab_entry>	main_head

%start program

%%

program:			  	  declarations functions main_function					{ ast = $$ = ast_program($1, $2, $3); }
						| declarations main_function							{ ast = $$ = ast_program($1, NULL, $2); }
						| functions main_function								{ ast = $$ = ast_program(NULL, $1, $2); }
						| main_function											{ ast = $$ = ast_program(NULL, NULL, $1); }
						;
declarations:			  declarations declaration								{ $$ = list_add($1, $2); }
						| declaration											{ $$ = list_add(NULL, $1); }
						;
declaration:		  	  basic_type names T_SEMI								{ $$ = ast_declaration($1, $2); }
						;
basic_type:				  T_INT													{ $$ = INT_TYPE;	}
						| T_CHAR												{ $$ = CHAR_TYPE;	}
						| T_FLOAT												{ $$ = FLOAT_TYPE;	}
						| T_DOUBLE												{ $$ = DOUBLE_TYPE; }
						;
names:				 	  names T_COMMA var_init								{ $$ = list_add($1, $3); }
						| var_init												{ $$ = list_add(NULL, $1); }
						;
var_init:			 	  variable init											{ $$ = set_variable_init_value($1, $2); }
						;
variable:				  T_ID													{ $$ = insert_variable_entry($1, yylineno, UNDEF_TYPE);	}
						;
init:				 	  T_ASSIGN constant										{ $$ = $2->as.constant.val; }
						| /* empty */											{ $$.ival = 0; }
						;
constant:			 	  T_ICONST												{ $$ = ast_constant(   INT_TYPE, $1); }
						| T_FCONST												{ $$ = ast_constant(DOUBLE_TYPE, $1); }
						| T_CCONST												{ $$ = ast_constant(  CHAR_TYPE, $1); }
						;
functions:				  functions function									{ $$ = list_add($1, $2); }
						| function												{ $$ = list_add(NULL, $1); }
						;
function:			 	  function_head function_tail							{ $$ = ast_function($1, $2); }
						;
function_head:		 	  function_head_start parameters T_RPAREN				{ $$ = set_function_parameters($1, $2); }
						| function_head_start T_RPAREN							{ $$ = $1; /* parameters already NULL */ }							
						;
function_head_start: 	  basic_type T_ID T_LPAREN								{ $$ = insert_function_entry($2, yylineno, $1); 		enter_local_scope($2); }
						| T_VOID T_ID T_LPAREN									{ $$ = insert_function_entry($2, yylineno, VOID_TYPE);	enter_local_scope($2); }
						;
parameters:			 	  parameters T_COMMA parameter							{ $$ = list_add($1, $3); }
						| parameter												{ $$ = list_add(NULL, $1); }
						;
parameter:				  basic_type T_ID										{ $$ = insert_parameter_entry($2, yylineno, $1); }
						;
function_tail:			  T_LBRACE declarations statements T_RBRACE				{ hide_current_scope(); $$ = ast_function_tail($2, $3);  }
						| T_LBRACE statements T_RBRACE							{ hide_current_scope(); $$ = ast_function_tail(NULL, $2); }
						;
statements:			 	  statements statement									{ $$ = list_add($1, $2); }
						| statement												{ $$ = list_add(NULL, $1); }
						;
statement:				  if_statement											{ $$ = $1; }
						| for_loop												{ $$ = $1; }
						| while_loop											{ $$ = $1; }
						| assigment T_SEMI										{ $$ = $1; }
						| T_CONTINUE T_SEMI										{ $$ = ast_jump_statement(CONTINUE); }
						| T_BREAK T_SEMI										{ $$ = ast_jump_statement(BREAK); }
						| function_call T_SEMI									{ $$ = $1; }
						| var_ref T_INCDEC T_SEMI								{ $$ = ast_expression_unary($1, $2, POSTFIX); }
						| T_INCDEC var_ref T_SEMI								{ $$ = ast_expression_unary($2, $1, PREFIX); }
						| print_statement										{ $$ = $1; }
						| input_statement										{ $$ = $1; }
						| return_statement										{ $$ = $1; }
						;
if_statement:		 	  T_IF T_LPAREN expression T_RPAREN
							tail else_if optional_else							{ $$ = ast_if_statement($3, $5, $6, $7); }
						| T_IF T_LPAREN expression T_RPAREN
							tail optional_else									{ $$ = ast_if_statement($3, $5, NULL, $6); }
						;
expression:			 	  expression T_ADDOP expression							{ $$ = ast_expression_binary($1, $2, $3); }
						| expression T_MULOP expression							{ $$ = ast_expression_binary($1, $2, $3); }
						| var_ref T_INCDEC %prec INCDEC_POSTFIX					{ $$ = ast_expression_unary($1, $2, POSTFIX); }
						| T_INCDEC var_ref %prec INCDEC_PREFIX					{ $$ = ast_expression_unary($2, $1, PREFIX); }
						| expression T_OROP expression							{ $$ = ast_expression_binary($1, $2, $3); }
						| expression T_ANDOP expression							{ $$ = ast_expression_binary($1, $2, $3); }
						| T_NOTOP expression									{ $$ = ast_expression_unary($2, $1, PREFIX); }
						| expression T_EQUOP expression							{ $$ = ast_expression_binary($1, $2, $3); }
						| expression T_RELOP expression							{ $$ = ast_expression_binary($1, $2, $3); }
						| T_LPAREN expression T_RPAREN							{ $$ = $2; }
						| var_ref												{ $$ = $1; }
						| constant												{ $$ = $1; }
						| T_ADDOP constant %prec UNARY_PLUS_MINUS				{ $$ = ast_expression_unary($2, $1, PREFIX); }
						| function_call											{ $$ = $1; }
						;
var_ref:			 	  variable												{ $$ = ast_variable_reference($1); }
						; 
function_call:			  variable T_LPAREN arguments T_RPAREN					{ $$ = ast_function_call($1, $3); }
						| variable T_LPAREN T_RPAREN							{ $$ = ast_function_call($1, NULL); }
						;
arguments:		  		  arguments T_COMMA argument							{ $$ = list_add($1, $3); }
						| argument												{ $$ = list_add(NULL, $1); }
						;
argument:				  var_ref												{ $$ = $1; }
						| constant												{ $$ = $1; }
						| T_ADDOP constant %prec UNARY_PLUS_MINUS				{ $$ = ast_expression_unary($2, $1, PREFIX); }
						;
tail:				 	  T_LBRACE statements T_RBRACE							{ $$ = $2; }
						;
else_if:				  else_if T_ELSE T_IF
							T_LPAREN expression T_RPAREN tail					{ $$ = list_add($1, ast_else_if($5, $7)); }
						| T_ELSE T_IF
							T_LPAREN expression T_RPAREN tail					{ $$ = list_add(NULL, ast_else_if($4, $6)); }
						;
optional_else:		  	  T_ELSE tail											{ $$ = $2; }
						| /* empty */											{ $$ = NULL; }
						;
for_loop:			 	  T_FOR T_LPAREN assigment T_SEMI
							expression T_SEMI
							var_ref T_INCDEC T_RPAREN tail						{ $$ = ast_for_loop($3, $5, ast_expression_unary($7, $8, POSTFIX), $10); }
						;
assigment:			 	  var_ref T_ASSIGN expression							{ $$ = ast_assignment($1, $3); }
						;
while_loop:				  T_WHILE T_LPAREN expression T_RPAREN tail				{ $$ = ast_while_loop($3, $5); }
						;
print_statement:		  T_PRINT expression T_SEMI								{ $$ = ast_print_statement(EXPRESSION, NULL, $2); }
						| T_PRINT T_STRING T_SEMI								{ $$ = ast_print_statement(STRING, $2, NULL); }
						;
input_statement:		  T_INPUT var_ref T_SEMI								{ $$ = ast_input_statement($2); }
						;
return_statement:		  T_RETURN expression T_SEMI							{ $$ = ast_return_statement(UNDEF_TYPE, $2); }
						| T_RETURN T_SEMI										{ $$ = ast_return_statement(VOID_TYPE, NULL); }
						;
main_function:		 	  main_head function_tail								{ $$ = ast_function($1, $2); }
						;
main_head:				  T_INT T_MAIN T_LPAREN T_RPAREN						{ $$ = insert_function_entry("main", yylineno, INT_TYPE); enter_local_scope("main"); }							
						;

%%

void yyerror(){
	fprintf(stderr, "Syntax error at line %d\n", yylineno);
    exit(EXIT_FAILURE);
}
