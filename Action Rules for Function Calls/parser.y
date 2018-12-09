%{
	#include "semantics.c"
	#include "symtab.c"
	#include "ast.h"
	#include "ast.c"
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	extern FILE *yyin;
	extern FILE *yyout;
	extern int lineno;
	extern int yylex();
	void yyerror();
	
	// for declarations
	void add_to_names(list_t *entry);
	list_t **names;
	int nc = 0;
	
	// for the initializations of arrays
	void add_to_vals(Value val);
	Value *vals;
	int vc = 0;
	
	// for else ifs
	void add_elseif(AST_Node *elsif);
	AST_Node **elsifs;
	int elseif_count = 0;
	
	// for functions
	AST_Node_Func_Decl *temp_function;
%}

/* YYSTYPE union */
%union{
	// different types of values
	Value val;   
	
	// structures
	list_t* symtab_item;
	AST_Node* node;
	
	// for declarations
	int data_type;
	int const_type;
	
	// for arrays
	int array_size;
	
	// for parameters
	Param par;
}

/* token definition */
%token<val> CHAR INT FLOAT DOUBLE IF ELSE WHILE FOR CONTINUE BREAK VOID RETURN
%token<val> ADDOP MULOP DIVOP INCR OROP ANDOP NOTOP EQUOP RELOP
%token<val> LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE SEMI DOT COMMA ASSIGN REFER
%token <symtab_item> ID
%token <val> 	 ICONST
%token <val>  	 FCONST
%token <val> 	 CCONST
%token <val>     STRING

/* precedencies and associativities */
%left COMMA
%right ASSIGN
%left OROP
%left ANDOP
%left EQUOP
%left RELOP
%left ADDOP
%left MULOP DIVOP
%right NOTOP INCR REFER MINUS
%left LPAREN RPAREN LBRACK RBRACK

/* rule (non-terminal) definitions */
%type <node> program
%type <node> declarations declaration
%type <data_type> type
%type <symtab_item> variable
%type <array_size> array
%type <symtab_item> init var_init array_init
%type <node> constant
%type <node> expression var_ref
%type <node> statement assigment
%type <node> statements tail
%type <node> if_statement else_if optional_else
%type <node> for_statement while_statement
%type <node> functions_optional functions function
%type <node> parameters_optional parameters
%type <par>  parameter
%type <node> return_type
%type <node> function_call call_params call_param

%start program

%%

program: 
	declarations { ast_traversal($1); }
	statements   { ast_traversal($3); }
	RETURN SEMI functions_optional { ast_traversal($7); }
;

/* declarations */
declarations: 
	declarations declaration
	{
		AST_Node_Declarations *temp = (AST_Node_Declarations*) $1;
		$$ = new_declarations_node(temp->declarations, temp->declaration_count, $2);
	}
	| declaration
	{
		$$ = new_declarations_node(NULL, 0, $1);
	}
;

declaration: type { declare = 1; } names { declare = 0; } SEMI
	{
		int i;
		$$ = new_ast_decl_node($1, names, nc);
		nc = 0;
		
		AST_Node_Decl *temp = (AST_Node_Decl*) $$;
		
		// declare types of the names
		for(i=0; i < temp->names_count; i++){
			// variable
			if(temp->names[i]->st_type == UNDEF){
				set_type(temp->names[i]->st_name, temp->data_type, UNDEF);
			}
			// pointer
			else if(temp->names[i]->st_type == POINTER_TYPE){
				set_type(temp->names[i]->st_name, POINTER_TYPE, temp->data_type);
			}
			// array
			else if(temp->names[i]->st_type == ARRAY_TYPE){
				set_type(temp->names[i]->st_name, ARRAY_TYPE, temp->data_type);
			}
		}
	}
;

type: INT  		{ $$ = INT_TYPE;   }
	| CHAR 		{ $$ = CHAR_TYPE;  }
	| FLOAT 	{ $$ = REAL_TYPE;  }
	| DOUBLE 	{ $$ = REAL_TYPE;  }
	| VOID 		{ $$ = VOID_TYPE;  }
;

names: names COMMA variable
	{
		add_to_names($3);
	}
	| names COMMA init
	{
		add_to_names($3);
	}
	| variable
	{
		add_to_names($1);
	}
	| init
	{ 
		add_to_names($1);
	}
;

variable: ID { $$ = $1; }
	| pointer ID
	{
		$2->st_type = POINTER_TYPE;
		$$ = $2;
	}
	| ID array
	{
		$1->st_type = ARRAY_TYPE;
		$1->array_size = $2;
		$$ = $1;
	}
;

pointer: pointer MULOP | MULOP ; /* for now we suppose everything is a simple pointer! */

array: array LBRACK expression RBRACK
	{ 
	    // if declaration then error!
		if(declare == 1){
			fprintf(stderr, "Array declaration at %d contains expression!\n", lineno);
			exit(1);
		}
	}
	| LBRACK expression RBRACK
	{
		// if declaration then error!
		if(declare == 1){
			fprintf(stderr, "Array declaration at %d contains expression!\n", lineno);
			exit(1);
		}
	}
	| LBRACK ICONST RBRACK
	{
		// set array_size for declaration purposes
		$$ = $2.ival;
	}
;

init:
	var_init { $$ = $1; }
	| array_init { $$ = $1; }
; 

var_init : ID ASSIGN constant
{ 
	AST_Node_Const *temp = (AST_Node_Const*) $$;
	$1->val = temp->val;
	$1->st_type = temp->const_type;
	$$ = $1;
}
;

array_init: ID array ASSIGN LBRACE values RBRACE
{
	if($1->array_size != vc){
	    fprintf(stderr, "Array init at %d doesn't contain the right amount of values!\n", lineno);
		exit(1);
	}
	$1->vals = vals;
	$1->array_size = $2;
	$$ = $1;
	vc = 0;
}
;

values: values COMMA constant 
	{
		AST_Node_Const *temp = (AST_Node_Const*) $3;
		add_to_vals(temp->val);
	}
	| constant
	{
		AST_Node_Const *temp = (AST_Node_Const*) $1;
		add_to_vals(temp->val);
	}
;

/* statements */
statements:
	statements statement
	{
		AST_Node_Statements *temp = (AST_Node_Statements*) $1;
		$$ = new_statements_node(temp->statements, temp->statement_count, $2);
	}
	| statement
	{
		$$ = new_statements_node(NULL, 0, $1);
	}
;

statement:
	if_statement
	{ 
		$$ = $1; /* just pass information */
	}
	| for_statement
	{ 
		$$ = $1; /* just pass information */
	}
	| while_statement
	{
		$$ = $1; /* just pass information */
	}
	| assigment SEMI
	{
		$$ = $1; /* just pass information */
	}
	| CONTINUE SEMI
	{ 
		$$ = new_ast_simple_node(0);
	}
	| BREAK SEMI
	{ 
		$$ = new_ast_simple_node(1);
	}
	| function_call SEMI
	{ 
		$$ = $1; /* just pass information */
	}
	| ID INCR SEMI
	{
		/* increment */
		if($2.ival == INC){
			$$ = new_ast_incr_node($1, 0, 0);
		}
		else{
			$$ = new_ast_incr_node($1, 1, 0);
		}
	}
	| INCR ID SEMI
	{
		/* increment */
		if($1.ival == INC){
			$$ = new_ast_incr_node($2, 0, 1);
		}
		else{
			$$ = new_ast_incr_node($2, 1, 1);
		}
	}
;

if_statement:
	IF LPAREN expression RPAREN tail else_if optional_else
	{
		$$ = new_ast_if_node($3, $5, elsifs, elseif_count, $7);
		elseif_count = 0;
		elsifs = NULL;
	}
	| IF LPAREN expression RPAREN tail optional_else
	{
		$$ = new_ast_if_node($3, $5, NULL, 0, $6);
	}
;

else_if:
	else_if ELSE IF LPAREN expression RPAREN tail
	{
		AST_Node *temp = new_ast_elsif_node($5, $7);
		add_elseif(temp);
	}
	| ELSE IF LPAREN expression RPAREN tail
	{
		AST_Node *temp = new_ast_elsif_node($4, $6);
		add_elseif(temp);
	}
;

optional_else:
	ELSE tail
	{
		/* else exists */
		$$ = $2;
	}
	| /* empty */
	{
		/* no else */
		$$ = NULL;
	}
;

for_statement: FOR LPAREN assigment SEMI expression SEMI ID INCR RPAREN tail
{
	/* create increment node*/
	AST_Node *incr_node;
	if($8.ival == INC){ /* increment */
		incr_node = new_ast_incr_node($7, 0, 0);
	}
	else{
		incr_node = new_ast_incr_node($7, 1, 0);
	}

	$$ = new_ast_for_node($3, $5, incr_node, $10);
	set_loop_counter($$);
}
;

while_statement: WHILE LPAREN expression RPAREN tail
{
	$$ = new_ast_while_node($3, $5);
}
;

tail: LBRACE statements RBRACE
{ 
	$$ = $2; /* just pass information */
}
;

expression:
    expression ADDOP expression
	{ 
	    $$ = new_ast_arithm_node($2.ival, $1, $3);
	}
	| expression MULOP expression
	{
	    $$ = new_ast_arithm_node(MUL, $1, $3);
	}
	| expression DIVOP expression
	{
		$$ = new_ast_arithm_node(DIV, $1, $3);
	}
	| ID INCR
	{
		/* increment */
		if($2.ival == INC){
			$$ = new_ast_incr_node($1, 0, 0);
		}
		else{
			$$ = new_ast_incr_node($1, 1, 0);
		}	
	}
	| INCR ID
	{
		/* increment */
		if($1.ival == INC){
			$$ = new_ast_incr_node($2, 0, 1);
		}
		else{
			$$ = new_ast_incr_node($2, 1, 1);
		}
	}
	| expression OROP expression
	{
		$$ = new_ast_bool_node(OR, $1, $3);
	}
	| expression ANDOP expression
	{
		$$ = new_ast_bool_node(AND, $1, $3);
	}
	| NOTOP expression
	{
	    $$ = new_ast_bool_node(NOT, $2, NULL);
	}
	| expression EQUOP expression
	{
		$$ = new_ast_equ_node($2.ival, $1, $3);
	}
	| expression RELOP expression
	{
		$$ = new_ast_rel_node($2.ival, $1, $3);
	}
	| LPAREN expression RPAREN
	{
		$$ = $2; /* just pass information */
	}
	| var_ref
	{ 
		$$ = $1; /* just pass information */
	}
	| constant
	{
		$$ = $1; /* no sign */
	}
	| ADDOP constant %prec MINUS
	{
		/* plus sign error */
		if($1.ival == ADD){
			fprintf(stderr, "Error having plus as a sign!\n");
			exit(1);
		}
		else{
			AST_Node_Const *temp = (AST_Node_Const*) $2;
		
			/* inverse value depending on the constant type */
			switch(temp->const_type){
				case INT_TYPE:
					temp->val.ival *= -1;
					break;
				case REAL_TYPE:
					temp->val.fval *= -1;
					break;
				case CHAR_TYPE:
					/* sign before char error */
					fprintf(stderr, "Error having sign before character constant!\n");
					exit(1);
					break;
			}
			
			$$ = (AST_Node*) temp;
		}
	}
	| function_call
	{
		$$ = $1; /* just pass information */
	}
;

constant:
	ICONST   { $$ = new_ast_const_node(INT_TYPE, $1);  }
	| FCONST { $$ = new_ast_const_node(REAL_TYPE, $1); }
	| CCONST { $$ = new_ast_const_node(CHAR_TYPE, $1); }
;

assigment: var_ref ASSIGN expression
{
	AST_Node_Ref *temp = (AST_Node_Ref*) $1;
	$$ = new_ast_assign_node(temp->entry, temp->ref, $3);
}
;

var_ref: variable
	{
		$$ = new_ast_ref_node($1, 0); /* no reference */
	}
	| REFER variable
	{
		$$ = new_ast_ref_node($2, 1); /* reference */
	}
; 

function_call: ID LPAREN call_params RPAREN
{	
	AST_Node_Call_Params *temp = (AST_Node_Call_Params*) $3;
	$$ = new_ast_func_call_node($1, temp->params, temp->num_of_pars);
}
;

call_params: 
	call_param
	{
		$$ = $1;
	}
	| STRING
	{
		AST_Node *temp = new_ast_const_node(STR_TYPE, $1);
		$$ = new_ast_call_params_node(NULL, 0, temp);
	}
	| /* empty */
	{
		AST_Node_Call_Params *temp = malloc (sizeof (AST_Node_Call_Params));
		temp->type = CALL_PARAMS;
		temp->params = NULL;
		temp->num_of_pars = 0;
		$$ = (AST_Node*)temp;
	}
;

call_param: 
	call_param COMMA expression
	{
		AST_Node_Call_Params *temp = (AST_Node_Call_Params*) $1;
		$$ = new_ast_call_params_node(temp->params, temp->num_of_pars, $3);
	}
	| expression
	{
		$$ = new_ast_call_params_node(NULL, 0, $1);
	}	
;

/* functions */
functions_optional: 
	functions
	{
		$$ = $1;
	}
	| /* empty */
	{
		$$ = NULL;
	}
;

functions: 
	functions function
	{
		AST_Node_Func_Declarations *temp = (AST_Node_Func_Declarations*) $1;
		$$ = new_func_declarations_node(temp->func_declarations, temp->func_declaration_count, $2);
	}
	| function
	{
		$$ = new_func_declarations_node(NULL, 0, $1);
	}
;

function: { incr_scope(); } function_head function_tail
{ 
	hide_scope();
	$$ = (AST_Node *) temp_function;
} 
;

function_head: { declare = 1; } return_type ID LPAREN
	{ 
		declare = 0;
		
		AST_Node_Ret_Type *temp = (AST_Node_Ret_Type *) $2;
		temp_function = (AST_Node_Func_Decl *) new_ast_func_decl_node(temp->ret_type, temp->pointer, $3);
		temp_function->entry->st_type = FUNCTION_TYPE;
		temp_function->entry->inf_type = temp->ret_type;
	}
	parameters_optional RPAREN
	{
		if($6 != NULL){
			AST_Node_Decl_Params *temp = (AST_Node_Decl_Params *) $6;
			
			temp_function->entry->parameters = temp->parameters;
			temp_function->entry->num_of_pars = temp->num_of_pars;
		}
		else{
			temp_function->entry->parameters = NULL;
			temp_function->entry->num_of_pars = 0;
		}		
	}
;

return_type:
	type
	{
		$$ = new_ast_ret_type_node($1, 0);
	}
	| type pointer
	{
		$$ = new_ast_ret_type_node($1, 1);
	}
;

parameters_optional: 
	parameters
	{
		$$ = $1;
	}
	| /* empty */
	{
		$$ = NULL;
	}
;

parameters: 
	parameters COMMA parameter
	{
		AST_Node_Decl_Params *temp = (AST_Node_Decl_Params *) $1;
		$$ = new_ast_decl_params_node(temp->parameters, temp->num_of_pars, $3);
	}
	| parameter
	{
		$$ = new_ast_decl_params_node(NULL, 0, $1);
	}
;

parameter : { declare = 1; } type variable
{ 
	declare = 0;
	$$ = def_param($2, $3->st_name, 0);
}
;

function_tail: LBRACE declarations_optional statements_optional return_optional RBRACE ;

declarations_optional: 
	declarations 
	{
		temp_function->declarations = $1;
	}
	| /* empty */
	{
		temp_function->declarations = NULL;
	}
;

statements_optional: 
	statements
	{
		temp_function->statements = $1;
	} 
	| /* empty */
	{
		temp_function->statements = NULL;
	}
;

return_optional:
	RETURN expression SEMI
	{
		temp_function->return_node = new_ast_return_node(temp_function->ret_type, $2);
	}
	| /* empty */
	{
		temp_function->return_node = NULL;
	}
;

%%

void yyerror ()
{
  fprintf(stderr, "Syntax error at line %d\n", lineno);
  exit(1);
}

void add_to_names(list_t *entry){
	// first entry
	if(nc == 0){
		nc = 1;
		names = (list_t **) malloc( 1 * sizeof(list_t *));
		names[0] = entry;
	}
	// general case
	else{
		nc++;
		names = (list_t **) realloc(names, nc * sizeof(list_t *));
		names[nc - 1] = entry;		
	}
}

void add_to_vals(Value val){
	// first entry
	if(vc == 0){
		vc = 1;
		vals = (Value *) malloc(1 * sizeof(Value));
		vals[0] = val;
	}
	// general case
	else{
		vc++;
		vals = (Value *) realloc(vals, vc * sizeof(Value));
		vals[vc - 1] = val;
	}
}

void add_elseif(AST_Node *elsif){
	// first entry
	if(elseif_count == 0){
		elseif_count = 1;
		elsifs = (AST_Node **) malloc(1 * sizeof(AST_Node));
		elsifs[0] = elsif;
	}
	// general case
	else{
		elseif_count++;
		elsifs = (AST_Node **) realloc(elsifs, elseif_count * sizeof(AST_Node));
		elsifs[elseif_count - 1] = elsif;
	}
}

int main (int argc, char *argv[]){
	
	// initialize symbol table
	init_hash_table();
	
	// initialize revisit queue
	queue = NULL;
	
	// parsing
	int flag;
	yyin = fopen(argv[1], "r");
	flag = yyparse();
	fclose(yyin);
	
	printf("Parsing finished!\n");
	
	if(queue != NULL){
		printf("Warning: Something has not been checked in the revisit queue!\n");
	}
	
	// symbol table dump
	yyout = fopen("symtab_dump.out", "w");
	symtab_dump(yyout);
	fclose(yyout);
	
	// revisit queue dump
	yyout = fopen("revisit_dump.out", "w");
	revisit_dump(yyout);
	fclose(yyout);
	
	return flag;
}
