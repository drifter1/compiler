%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "../include/compiler.h"
%}

/* YYSTYPE union */
%union{
    // different types of values
	Value val;   

    // structures
	list_t* symtab_item;
    AST_Node* ast_node;
	list_node* list_node;

    // for declarations
	int data_type;
	
	// for arrays
	int array_size;

	// for function head
	_function_head function_head_helper;

	// for function tail
	_function_tail function_tail_helper;

    // for parameters
	Param par;
}

/* token definition */
%token BREAK CHAR CONTINUE DOUBLE
%token ELSE FLOAT FOR IF
%token INT RETURN VOID WHILE
%token ASSIGN
%token <val> ADDOP INCDEC EQUOP RELOP
%token MULOP DIVOP OROP ANDOP NOTOP REFER
%token LPAREN RPAREN LBRACK RBRACK
%token LBRACE RBRACE SEMI COMMA
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
%right NOTOP INCDEC REFER MINUS
%left LPAREN RPAREN LBRACK RBRACK SUFFIX

/* rule (non-terminal) definitions */
%type <ast_node> program
%type <ast_node> declarations declaration
%type <data_type> type
%type <list_node> names
%type <symtab_item> variable
%type <array_size> array
%type <symtab_item> init var_init array_init
%type <list_node> values
%type <ast_node> constant
%type <ast_node> expression var_ref
%type <ast_node> statement assigment
%type <ast_node> statements tail
%type <ast_node> if_statement
%type <list_node> else_if
%type <ast_node> optional_else
%type <ast_node> for_statement while_statement
%type <ast_node> functions_optional functions function
%type <function_head_helper> function_head
%type <ast_node> parameters_optional parameters
%type <par>  parameter
%type <ast_node> return_type
%type <ast_node> function_call call_params call_param
%type <function_tail_helper> function_tail
%type <ast_node> declarations_optional statements_optional return_optional

%start program

%%

program: 
	declarations statements RETURN SEMI functions_optional { ast = $$ = new_program_node($1, $2, $5); }
;


/* declarations */
declarations: 
	declarations declaration { $$ = new_declarations_node($1, $2); }
	| declaration { $$ = new_declarations_node(NULL, $1); }
;

declaration:
	type { declare = 1; } names { declare = 0; } SEMI { $$ = new_ast_decl_node($1, $3, list_length($3)); }
;

type: INT  		{ $$ = INT_TYPE;   }
	| CHAR 		{ $$ = CHAR_TYPE;  }
	| FLOAT 	{ $$ = REAL_TYPE;  }
	| DOUBLE 	{ $$ = REAL_TYPE;  }
	| VOID 		{ $$ = VOID_TYPE;  }
;

names: names COMMA variable { $$ = list_add($1, $3);	}
	| names COMMA init 		{ $$ = list_add($1, $3);	}
	| variable 				{ $$ = list_add(NULL, $1);	}
	| init 					{ $$ = list_add(NULL, $1);	}
;

variable: 
	ID
	{
		$$ = $1; /* just pass information */
	}
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

pointer: MULOP ; /* for now only single pointers! */

array: /* for now only one-dimensional arrays */
	LBRACK expression RBRACK 
	{
		if (declare == 1) {
			// if declaration and not constant node then error!
			if ($2->type != CONST_NODE){
				fprintf(stderr, "Semantic error at line %d. Array declaration contains expression\n", yylineno);
    			exit(EXIT_FAILURE);
			}
			
			AST_Node_Const *temp = (AST_Node_Const*) $2;

			if (temp->const_type != INT_TYPE) {
				fprintf(stderr, "Semantic error at line %d. Array declaration contains non-integer constant\n", yylineno);
    			exit(EXIT_FAILURE);
			}

			// set array_size for declaration purposes
			$$ = temp->val.ival;
		}
	}
;

init:
	var_init { $$ = $1; }
	| array_init { $$ = $1; }
; 

var_init : ID ASSIGN constant
    { 
        AST_Node_Const *temp = (AST_Node_Const*) $3;
        $1->val = temp->val;
        $1->st_type = temp->const_type;
        $$ = $1;
    }
;

array_init: ID array ASSIGN LBRACE values RBRACE
    {
        if($2 != list_length($5)){
			fprintf(stderr, "Semantic error at line %d. Array init doesn't contain the right amount of values\n", yylineno);
			exit(EXIT_FAILURE);
        }
        $1->vals = $5;
        $1->array_size = $2;
        $$ = $1;
    }
;

values: values COMMA constant 	{ $$ = list_add($1, $3); 	}
	| constant 					{ $$ = list_add(NULL, $1); 	}
;


/* statements */
statements:
	statements statement { $$ = new_statements_node($1, $2); }
	| statement { $$ = new_statements_node(NULL, $1); }
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
	| ID INCDEC SEMI
	{
		/* increment */
		if($2.ival == INC){
			$$ = new_ast_incr_node($1, 0, 0);
		}
		else{
			$$ = new_ast_incr_node($1, 1, 0);
		}
	}
	| INCDEC ID SEMI
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
		$$ = new_ast_if_node($3, $5, $6, list_length($6), $7);
	}
	| IF LPAREN expression RPAREN tail optional_else
	{
		$$ = new_ast_if_node($3, $5, NULL, 0, $6);
	}
;


else_if:
	else_if ELSE IF LPAREN expression RPAREN tail
	{
		$$ = list_add($1, new_ast_elsif_node($5, $7));
	}
	| ELSE IF LPAREN expression RPAREN tail
	{	
		$$ = list_add(NULL, new_ast_elsif_node($4, $6));
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

for_statement: FOR LPAREN assigment SEMI expression SEMI ID INCDEC RPAREN tail
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
	| ID INCDEC %prec SUFFIX
	{
		/* increment */
		if($2.ival == INC){
			$$ = new_ast_incr_node($1, 0, 0);
		}
		else{
			$$ = new_ast_incr_node($1, 1, 0);
		}
	}
	| INCDEC ID
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
			fprintf(stderr, "Semantic error at line %d. Plus sign is used as a constant sign\n", yylineno);
			exit(EXIT_FAILURE);
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
					fprintf(stderr, "Semantic error at line %d. Sign before character constant\n", yylineno);
					exit(EXIT_FAILURE);
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
		
		/* find datatypes */
		int type1 = get_type(temp->entry->st_name);
		int type2 = expression_data_type($3);
		
		/* check assignment semantics */
		get_result_type(
			type1,       /*  variable datatype  */
			type2,       /* expression datatype */
			NONE  /* checking compatibility only (no operator) */
		);
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
		$$ = new_ast_call_params_node(NULL, temp);
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
	call_param COMMA expression { $$ = new_ast_call_params_node($1, $3); }
	| expression { $$ = new_ast_call_params_node(NULL, $1); }	
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
	functions function { $$ = new_func_declarations_node($1, $2); }
	| function { $$ = new_func_declarations_node(NULL, $1); }
;


function: { incr_scope(); } function_head function_tail
    { 	
		hide_scope();

		$$ = new_ast_func_decl_node($2.ret_type, $2.entry, $2.decl_params,
				$3.declarations, $3.statements, $3.return_node);        
    } 
;

function_head: { function_decl = 1; } return_type ID LPAREN parameters_optional RPAREN
	{ 
		function_decl = 0;

		$$.ret_type = $2;
		$$.entry = $3;
		$$.decl_params = $5;
	}
;

return_type:
	type { $$ = new_ast_ret_type_node($1, 0); }
	| type pointer { $$ = new_ast_ret_type_node($1, 1);	}
;

parameters_optional: 
	parameters { $$ = $1; }
	| /* empty */ { $$ = NULL; }
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
        
        // set type of symbol table entry	
        if($3->st_type == UNDEF){ /* "simple" type */
            set_type($3->st_name, $2, UNDEF); 
        }
        else if($3->st_type == POINTER_TYPE){ /* pointer */
            set_type($3->st_name, POINTER_TYPE, $2);
        }
        else if($3->st_type == ARRAY_TYPE){ /* array  */
            set_type($3->st_name, ARRAY_TYPE, $2);
        }
        
        /* define parameter */
        $$ = def_param($2, $3->st_name, 0);
    }
;

function_tail: LBRACE declarations_optional statements_optional return_optional RBRACE 
	{
		$$.declarations = $2; 
		$$.statements = $3;
		$$.return_node = $4;
	}
;

declarations_optional:
	declarations { $$ = $1;}
	| /* empty */ {	$$ = NULL; }
;

statements_optional: 
	statements { $$ = $1; } 
	| /* empty */ { $$ = NULL; }
;

return_optional:
	RETURN expression SEMI { $$ = new_ast_return_node($2); }
	| /* empty */ { $$ = NULL; }
;

%%

void yyerror(){
	fprintf(stderr, "Syntax error at line %d\n", yylineno);
    exit(EXIT_FAILURE);
}
