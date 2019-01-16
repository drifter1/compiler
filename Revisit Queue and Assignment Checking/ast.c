#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* flag variable that shows revisit in assignment expression */
int cont_revisit = 0; // 1: contains revisit, 0: not

/* ------------------AST NODE MANAGEMENT-------------------- */
/* The basic node */
AST_Node *new_ast_node(Node_Type type, AST_Node *left, AST_Node *right){
	// allocate memory
	AST_Node *v = malloc (sizeof (AST_Node));
	
	// set entries
	v->type = type;
	v->left = left;
	v->right = right;
	
	// return the result
	return v;
}

/* Declarations */
AST_Node *new_declarations_node(AST_Node **declarations, int declaration_count, AST_Node *declaration){
	// allocate memory
	AST_Node_Declarations *v = malloc (sizeof (AST_Node_Declarations));
	
	// set node type
	v->type = DECLARATIONS;
	
	// first declaration
	if(declarations == NULL){
		declarations = (AST_Node**) malloc (sizeof (AST_Node*));
		declarations[0] = declaration;
		declaration_count = 1;
	}
	// add new declaration
	else{
		declarations = (AST_Node**) realloc (declarations, (declaration_count + 1) * sizeof (AST_Node*));
		declarations[declaration_count] = declaration;
		declaration_count++;
	}
	
	// set entries
	v->declarations = declarations;
	v->declaration_count = declaration_count;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_decl_node(int data_type, list_t **names, int names_count){
	// allocate memory
	AST_Node_Decl *v = malloc (sizeof (AST_Node_Decl));
	
	// set entries
	v->type = DECL_NODE;
	v->data_type = data_type;
	v->names = names;
	v->names_count = names_count;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_const_node(int const_type, Value val){
	// allocate memory
	AST_Node_Const *v = malloc (sizeof (AST_Node_Const));
	
	// set entries
	v->type = CONST_NODE;
	v->const_type = const_type;
	v->val = val;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

/* Statements */

AST_Node *new_statements_node(AST_Node **statements, int statement_count, AST_Node *statement){
	// allocate memory
	AST_Node_Statements *v = malloc (sizeof (AST_Node_Statements));
	
	// set node type
	v->type = STATEMENTS;
	
	// first statement
	if(statements == NULL){
		statements = (AST_Node**) malloc (sizeof (AST_Node*));
		statements[0] = statement;
		statement_count = 1;
	}
	// add new statement
	else{
		statements = (AST_Node**) realloc (statements, (statement_count + 1) * sizeof (AST_Node*));
		statements[statement_count] = statement;
		statement_count++;
	}
	
	// set entries
	v->statements = statements;
	v->statement_count = statement_count;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_if_node(AST_Node *condition, AST_Node *if_branch, AST_Node **elsif_branches,
	int elseif_count, AST_Node *else_branch){
	// allocate memory
	AST_Node_If *v = malloc (sizeof (AST_Node_If));
	
	// set entries
	v->type = IF_NODE;
	v->condition = condition;
	v->if_branch = if_branch;
	v->elsif_branches = elsif_branches;
	v->elseif_count = elseif_count;
	v->else_branch = else_branch;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_elsif_node(AST_Node *condition, AST_Node *elsif_branch){
	// allocate memory
	AST_Node_Elsif *v = malloc (sizeof (AST_Node_Elsif));
	
	// set entries
	v->type = ELSIF_NODE;
	v->condition = condition;
	v->elsif_branch = elsif_branch;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_for_node(AST_Node *initialize, AST_Node *condition, AST_Node *increment, AST_Node *for_branch){
	// allocate memory
	AST_Node_For *v = malloc (sizeof (AST_Node_For));
	
	// set entries
	v->type = FOR_NODE;
	v->initialize = initialize;
	v->condition = condition;
	v->increment = increment;
	v->for_branch = for_branch;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

void set_loop_counter(AST_Node *node){
	/* type-cast to for node */
	AST_Node_For *for_node = (AST_Node_For *) node;
	
	/* find the counter */
	AST_Node_Assign *assign_node = (AST_Node_Assign *) for_node->initialize;
	for_node->counter = assign_node->entry;
	
	/* check if the same one occurs in increment! */
	AST_Node_Incr *incr_node = (AST_Node_Incr *) for_node->increment;
	if( strcmp(incr_node->entry->st_name, assign_node->entry->st_name) ){
		fprintf(stderr, "Variable used in init and incr of for are not the same!\n");
		exit(1);
	}	
	
	/* type-cast back to AST_Node */
	node = (AST_Node *) for_node;
}

AST_Node *new_ast_while_node(AST_Node *condition, AST_Node *while_branch){
	// allocate memory
	AST_Node_While *v = malloc (sizeof (AST_Node_While));
	
	// set entries
	v->type = WHILE_NODE;
	v->condition = condition;
	v->while_branch = while_branch;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_assign_node(list_t *entry, int ref, AST_Node *assign_val){
	// allocate memory
	AST_Node_Assign *v = malloc (sizeof (AST_Node_Assign));
	
	// set entries
	v->type = ASSIGN_NODE;
	v->entry = entry;
	v->ref = ref;
	v->assign_val = assign_val;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_simple_node(int statement_type){
	// allocate memory
	AST_Node_Simple *v = malloc (sizeof (AST_Node_Simple));
	
	// set entries
	v->type = SIMPLE_NODE;
	v->statement_type = statement_type;
	
	// return type-casted result
	return (struct AST_Node *) v;
}
 
AST_Node *new_ast_incr_node(list_t *entry, int incr_type, int pf_type){
	// allocate memory
	AST_Node_Incr *v = malloc (sizeof (AST_Node_Incr));
	
	// set entries
	v->type = INCR_NODE;
	v->entry = entry;
	v->incr_type = incr_type;
	v->pf_type = pf_type;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_func_call_node(list_t *entry, AST_Node **params, int num_of_pars){
	// allocate memory
	AST_Node_Func_Call *v = malloc (sizeof (AST_Node_Func_Call));
	
	// set entries
	v->type = FUNC_CALL;
	v->entry = entry;
	v->params = params;
	v->num_of_pars = num_of_pars;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_call_params_node(AST_Node **params, int num_of_pars, AST_Node *param){
	// allocate memory
	AST_Node_Call_Params *v = malloc (sizeof (AST_Node_Call_Params));
	
	// set type
	v->type = CALL_PARAMS;
	
	// first parameter
	if(params == NULL){
		params = (AST_Node**) malloc (sizeof (AST_Node*));
		params[0] = param;
		num_of_pars = 1;
	}
	// add new parameter
	else{
		params = (AST_Node**) realloc (params, (num_of_pars + 1) * sizeof (AST_Node*));
		params[num_of_pars] = param;
		num_of_pars++;
	}
	
	// set entries
	v->params = params;
	v->num_of_pars = num_of_pars;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

/* Expressions */

AST_Node *new_ast_arithm_node(enum Arithm_op op, AST_Node *left, AST_Node *right){
	// allocate memory
	AST_Node_Arithm *v = malloc (sizeof (AST_Node_Arithm));
	
	// set entries
	v->type = ARITHM_NODE;
	v->op = op;
	v->left = left;
	v->right = right;
	
	// set data type
	v->data_type = get_result_type(
			expression_data_type(left),  /* data type of left expression */
			expression_data_type(right), /* data type of right expression */
			ARITHM_OP                    /* operation type */
	);
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_bool_node(enum Bool_op op, AST_Node *left, AST_Node *right){
	// allocate memory
	AST_Node_Bool *v = malloc (sizeof (AST_Node_Bool));
	
	// set entries
	v->type = BOOL_NODE;
	v->op = op;
	v->left = left;
	v->right = right;
	
	// set data type
	if(v->op != NOT){ /* AND or OR */
		v->data_type = get_result_type(
			expression_data_type(left),  /* data type of left expression */
			expression_data_type(right), /* data type of right expression */
			BOOL_OP                      /* operation type */
		);	
	}
	else{ /* NOT */
		v->data_type = get_result_type(
			expression_data_type(left), /* data type of left expression */
			UNDEF,                      /* there is no right expression */
			NOT_OP                      /* operation type */
		);	
	}
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_rel_node(enum Rel_op op, AST_Node *left, AST_Node *right){
	// allocate memory
	AST_Node_Rel *v = malloc (sizeof (AST_Node_Rel));
	
	// set entries
	v->type = REL_NODE;
	v->op = op;
	v->left = left;
	v->right = right;
	
	// set data type
	v->data_type = get_result_type(
			expression_data_type(left),  /* data type of left expression  */
			expression_data_type(right), /* data type of right expression */
			REL_OP                       /* operation type */
	);
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_equ_node(enum Equ_op op, AST_Node *left, AST_Node *right){
	// allocate memory
	AST_Node_Equ *v = malloc (sizeof (AST_Node_Equ));
	
	// set entries
	v->type = EQU_NODE;
	v->op = op;
	v->left = left;
	v->right = right;
	
	// set data type
	v->data_type = get_result_type(
			expression_data_type(left),  /* data type of left expression  */
			expression_data_type(right), /* data type of right expression */
			EQU_OP                       /* operation type */
	);
	
	// return type-casted result
	return (struct AST_Node *) v;	
}

AST_Node *new_ast_ref_node(list_t *entry, int ref){
	// allocate memory
	AST_Node_Ref *v = malloc (sizeof (AST_Node_Ref));
	
	// set entries
	v->type = REF_NODE;
	v->entry = entry;
	v->ref = ref;
	
	// return type-casted result
	return (struct AST_Node *) v;	
}

int expression_data_type(AST_Node *node){
	/* temp nodes */
	AST_Node_Arithm *temp_arithm;
	AST_Node_Incr *temp_incr;
	AST_Node_Bool *temp_bool;
	AST_Node_Rel *temp_rel;
	AST_Node_Equ *temp_equ;
	AST_Node_Ref *temp_ref;
	AST_Node_Const *temp_const;
	AST_Node_Func_Call *temp_func_call;
	
	/* return type depends on the AST node type */
	switch(node->type){
		case ARITHM_NODE: /* arithmetic expression */
			temp_arithm = (AST_Node_Arithm *) node;
			
			/* set datatype again */
			temp_arithm->data_type = get_result_type(
				expression_data_type(temp_arithm->left),  /* data type of left expression */
				expression_data_type(temp_arithm->right), /* data type of right expression */
				ARITHM_OP                    /* operation type */
			);
			
			return temp_arithm->data_type; 
			break;
		case INCR_NODE:   /* special case of increment */
			temp_incr = (AST_Node_Incr *) node;
			return temp_incr->entry->st_type;
			break;
		case BOOL_NODE:   /* boolean expression */
			temp_bool = (AST_Node_Bool *) node;
			
			/* set datatype again */
			if(temp_bool->op != NOT){ /* AND or OR */
				temp_bool->data_type = get_result_type(
					expression_data_type(temp_bool->left),  /* data type of left expression */
					expression_data_type(temp_bool->right), /* data type of right expression */
					BOOL_OP                      /* operation type */
				);	
			}
			else{ /* NOT */
				temp_bool->data_type = get_result_type(
					expression_data_type(temp_bool->left), /* data type of left expression */
					UNDEF,                      /* there is no right expression */
					NOT_OP                      /* operation type */
				);	
			}
			
			return temp_bool->data_type;
			break;
		case REL_NODE:    /* relational expression */
			temp_rel = (AST_Node_Rel *) node;
			
			/* set datatype again */
			temp_rel->data_type = get_result_type(
					expression_data_type(temp_rel->left),  /* data type of left expression  */
					expression_data_type(temp_rel->right), /* data type of right expression */
					REL_OP                       /* operation type */
			);
			
			return temp_rel->data_type;
			break;
		case EQU_NODE:    /* equality expression */
			temp_equ = (AST_Node_Equ *) node;
			
			/* set datatype again */
			temp_equ->data_type = get_result_type(
					expression_data_type(temp_equ->left),  /* data type of left expression  */
					expression_data_type(temp_equ->right), /* data type of right expression */
					EQU_OP                       /* operation type */
			);
			
			return temp_equ->data_type;
			break;
		case REF_NODE:    /* identifier reference */
			temp_ref = (AST_Node_Ref *) node;
			/* if "simple" type */
			int type = temp_ref->entry->st_type;
			if(type == INT_TYPE	|| type == REAL_TYPE || type == CHAR_TYPE){
				return temp_ref->entry->st_type;
			}
			/* if array or pointer */
			else{
				return temp_ref->entry->inf_type;
			}
			break;
		case CONST_NODE:  /* constant */
			temp_const = (AST_Node_Const *) node;
			return temp_const->const_type; /* constant data type */
			break;
		case FUNC_CALL:   /* function call */
			temp_func_call = (AST_Node_Func_Call *) node;
			
			/* check if it needs revisit */
			if(temp_func_call->entry->st_type == UNDEF){
				if(temp_func_call->entry->inf_type == UNDEF){
					cont_revisit = 1;  /* contains revisit */
					return INT_TYPE;   /*   dummy return   */
				}
			}
			
			return temp_func_call->entry->inf_type; /* return type */
			break;
		default: /* wrong choice case */
			fprintf(stderr, "Error in node selection!\n");
			exit(1);
	}
}

/* Functions */
AST_Node *new_func_declarations_node(AST_Node **func_declarations, int func_declaration_count, AST_Node *func_declaration){
	// allocate memory
	AST_Node_Func_Declarations *v = malloc (sizeof (AST_Node_Func_Declarations));
	
	// set node type
	v->type = FUNC_DECLS;
	
	// first declaration
	if(func_declarations == NULL){
		func_declarations = (AST_Node**) malloc (sizeof (AST_Node*));
		func_declarations[0] = func_declaration;
		func_declaration_count = 1;
	}
	// add new declaration
	else{
		func_declarations = (AST_Node**) realloc (func_declarations, (func_declaration_count + 1) * sizeof (AST_Node*));
		func_declarations[func_declaration_count] = func_declaration;
		func_declaration_count++;
	}
	
	// set entries
	v->func_declarations = func_declarations;
	v->func_declaration_count = func_declaration_count;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_func_decl_node(int ret_type, int pointer, list_t *entry){
	// allocate memory
	AST_Node_Func_Decl *v = malloc (sizeof (AST_Node_Func_Decl));
	
	// set entries
	v->type = FUNC_DECL;
	v->ret_type = ret_type;
	v->pointer = pointer;
	v->entry = entry;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_ret_type_node(int ret_type, int pointer){
	// allocate memory
	AST_Node_Ret_Type *v = malloc (sizeof (AST_Node_Ret_Type));
	
	// set entries
	v->type = RET_TYPE;
	v->ret_type = ret_type;
	v->pointer = pointer;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_decl_params_node(Param *parameters, int num_of_pars, Param param){
	// allocate memory
	AST_Node_Decl_Params *v = malloc (sizeof (AST_Node_Decl_Params));
	
	// set node type
	v->type = DECL_PARAMS;
	
	// first declaration
	if(parameters == NULL){
		parameters = (Param*) malloc (sizeof (Param));
		parameters[0] = param;
		num_of_pars = 1;
	}
	// add new declaration
	else{
		parameters = (Param*) realloc (parameters, (num_of_pars + 1) * sizeof (Param));
		parameters[num_of_pars] = param;
		num_of_pars++;
	}
	
	// set entries
	v->parameters = parameters;
	v->num_of_pars = num_of_pars;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_return_node(int ret_type, AST_Node *ret_val){
	// allocate memory
	AST_Node_Return *v = malloc (sizeof (AST_Node_Return));
	
	// set entries
	v->type = RETURN_NODE;
	v->ret_type = ret_type;
	v->ret_val = ret_val;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

/* Tree Traversal */

void ast_print_node(AST_Node *node){
	/* temp nodes */
	AST_Node_Declarations *temp_declarations;
	AST_Node_Decl *temp_decl;
	AST_Node_Const *temp_const;
	AST_Node_Statements *temp_statements;
	AST_Node_If *temp_if;
	AST_Node_For *temp_for;
	AST_Node_Assign *temp_assign;
	AST_Node_Simple *temp_simple;
	AST_Node_Incr *temp_incr;
	AST_Node_Func_Call *temp_func_call;
	AST_Node_Call_Params *temp_call_params;
	AST_Node_Arithm *temp_arithm;
	AST_Node_Bool *temp_bool;
	AST_Node_Rel *temp_rel;
	AST_Node_Equ *temp_equ;
	AST_Node_Ref *temp_ref;
	AST_Node_Func_Declarations *temp_func_declarations;
	AST_Node_Func_Decl *temp_func_decl;
	AST_Node_Ret_Type *temp_ret_type;
	AST_Node_Decl_Params *temp_decl_params;
	AST_Node_Return *temp_return;
	
	switch(node->type){
		case BASIC_NODE:
			printf("Basic Node\n");
			break;
		case DECLARATIONS:
			temp_declarations = (struct AST_Node_Declarations *) node;
			printf("Declarations Node with %d declarations\n", temp_declarations->declaration_count);
			break;
		case DECL_NODE:
			temp_decl = (struct AST_Node_Decl *) node;
			printf("Declaration Node of data-type %d for %d names\n",
				temp_decl->data_type, temp_decl->names_count);
			break;
		case CONST_NODE:
			temp_const = (struct AST_Node_Const *) node;
			printf("Constant Node of const-type %d with value ", temp_const->const_type);
			switch(temp_const->const_type){
				case INT_TYPE:
					printf("%d\n", temp_const->val.ival);
					break;
				case REAL_TYPE:
					printf("%.2f\n", temp_const->val.fval);
					break;
				case CHAR_TYPE:
					printf("%c\n",  temp_const->val.cval);
					break;
				case STR_TYPE:
					printf("%s\n",  temp_const->val.sval);
					break;
			}
			break;
		case STATEMENTS:
			temp_statements = (struct AST_Node_Statements *) node;
			printf("Statements Node with %d statements\n", temp_statements->statement_count);
			break;
		case IF_NODE:
			temp_if = (struct AST_Node_If *) node;
			printf("If Node with %d elseifs and ", temp_if->elseif_count);
			if(temp_if->else_branch == NULL){
				printf("no else\n");
			}
			else{
				printf("else\n");
			}			
			break;
		case ELSIF_NODE:
			printf("Elsif Node\n");
			break;
		case FOR_NODE:
			temp_for = (struct AST_Node_For *) node;
			printf("For Node with loop counter %s\n", temp_for->counter->st_name);
			break;
		case WHILE_NODE:
			printf("While Node\n");
			break;
		case ASSIGN_NODE:
			temp_assign = (struct AST_Node_Assign *) node;
			printf("Assign Node of entry %s\n", temp_assign->entry->st_name);
			break;
		case SIMPLE_NODE:
			temp_simple = (struct AST_Node_Simple *) node;
			printf("Simple Node of statement %d\n", temp_simple->statement_type);
			break;
		case INCR_NODE:
			temp_incr = (struct AST_Node_Incr *) node;
			printf("Increment Node of entry %s being %d %d\n", 
				temp_incr->entry->st_name, temp_incr->incr_type, temp_incr->pf_type);
			break;
		case FUNC_CALL:
			temp_func_call = (struct AST_Node_Func_Call *) node;
			printf("Function Call Node of %s with %d parameters\n", 
				temp_func_call->entry->st_name, temp_func_call->num_of_pars);
			break;
		case CALL_PARAMS:
			temp_call_params = (struct AST_Node_Call_Params *) node;
			printf("Function Call Parameters Node with %d parameters\n", temp_call_params->num_of_pars);
			break;
		case ARITHM_NODE:
			temp_arithm = (struct AST_Node_Arithm *) node;
			printf("Arithmetic Node of operator %d with result type %d\n", temp_arithm->op, temp_arithm->data_type);
			break;
		case BOOL_NODE:
			temp_bool = (struct AST_Node_Bool *) node;
			printf("Boolean Node of operator %d\n", temp_bool->op);
			break;
		case REL_NODE:
			temp_rel = (struct AST_Node_Rel *) node;
			printf("Relational Node of operator %d\n", temp_rel->op);
			break;
		case EQU_NODE:
			temp_equ = (struct AST_Node_Equ *) node;
			printf("Equality Node of operator %d\n", temp_equ->op);
			break;
		case REF_NODE:
			temp_ref = (struct AST_Node_Ref *) node;
			printf("Reference Node of entry %s\n", temp_ref->entry->st_name);
			break;
		case FUNC_DECLS:
			temp_func_declarations = (struct AST_Node_Func_Declarations *) node;
			printf("Function Declarations Node with %d function declarations\n", temp_func_declarations->func_declaration_count);
			break;
		case FUNC_DECL:
			temp_func_decl = (struct AST_Node_Func_Decl *) node;
			printf("Function Declaration Node of %s with ret_type %d and %d parameters\n", 
				temp_func_decl->entry->st_name, temp_func_decl->ret_type, temp_func_decl->entry->num_of_pars);
			break;
		case RET_TYPE:
			temp_ret_type = (struct AST_Node_Ret_Type *) node;
			printf("Return type %d which is ", temp_ret_type->ret_type);
			if(temp_ret_type->pointer){
				printf("a pointer\n");
			}
			else{
				printf("not a pointer\n");
			}
			break;
		case DECL_PARAMS:
			temp_decl_params = (struct AST_Node_Decl_Params *) node;
			printf("Function declaration parameters node of %d parameters\n", temp_decl_params->num_of_pars);
			break;
		case RETURN_NODE:
			temp_return = (struct AST_Node_Return *) node;
			printf("Return Node of ret_type %d\n", temp_return->ret_type);
			break;
		default: /* wrong choice case */
			fprintf(stderr, "Error in node selection!\n");
			exit(1);
	}
}

void ast_traversal(AST_Node *node){
	int i;
	
	/* check if empty */
	if(node == NULL){
		return;
	}
	
	/* left and right child cases */
	if(node->type == BASIC_NODE || node->type == ARITHM_NODE || node->type == BOOL_NODE
	|| node->type == REL_NODE || node->type == EQU_NODE){
		//ast_traversal(node->left);
		//ast_traversal(node->right);
		ast_print_node(node); // postfix
	}
	/* declarations case */
	else if(node->type == DECLARATIONS){
		AST_Node_Declarations *temp_declarations = (struct AST_Node_Declarations *) node;	
		ast_print_node(node);	
		for(i = 0; i < temp_declarations->declaration_count; i++){
			ast_traversal(temp_declarations->declarations[i]);
		}
	}
	/* statements case */
	else if(node->type == STATEMENTS){
		AST_Node_Statements *temp_statements = (struct AST_Node_Statements *) node;	
		ast_print_node(node);	
		for(i = 0; i < temp_statements->statement_count; i++){
			ast_traversal(temp_statements->statements[i]);
		}
	}
	/* the if case */
	else if(node->type == IF_NODE){
		AST_Node_If *temp_if = (struct AST_Node_If *) node;	
		ast_print_node(node);
		
		printf("Condition:\n");
		ast_traversal(temp_if->condition);
		
		printf("If branch:\n");
		ast_traversal(temp_if->if_branch);
		
		if(temp_if->elseif_count > 0 ){
			printf("Else if branches:\n");
			for(i = 0; i < temp_if->elseif_count; i++){
				printf("Else if branch%d:\n", i);
				ast_traversal(temp_if->elsif_branches[i]);
			}	
		}
	
		if(temp_if->else_branch != NULL){
			printf("Else branch:\n");
			ast_traversal(temp_if->else_branch);
		}
	}
	/* the else if case */
	else if(node->type == ELSIF_NODE){
		AST_Node_Elsif *temp_elsif = (struct AST_Node_Elsif *) node;
		ast_print_node(node);
		ast_traversal(temp_elsif->condition);
		ast_traversal(temp_elsif->elsif_branch);
	}
	/* for case */
	else if(node->type == FOR_NODE){
		AST_Node_For *temp_for = (struct AST_Node_For *) node;
		ast_print_node(node);
		printf("Initialize:\n");
		ast_traversal(temp_for->initialize);
		printf("Condition:\n");
		ast_traversal(temp_for->condition);
		printf("Increment:\n");
		ast_traversal(temp_for->increment);
		printf("For branch:\n");
		ast_traversal(temp_for->for_branch);
	}
	/* while case */
	else if(node->type == WHILE_NODE){
		AST_Node_While *temp_while = (struct AST_Node_While *) node;
		ast_print_node(node);
		printf("Condition:\n");
		ast_traversal(temp_while->condition);
		printf("While branch:\n");
		ast_traversal(temp_while->while_branch);
	}
	/* assign case */
	else if(node->type == ASSIGN_NODE){
		AST_Node_Assign *temp_assign = (struct AST_Node_Assign *) node;
		ast_print_node(node);
		printf("Assigning:\n");
		ast_traversal(temp_assign->assign_val);
	}
	/* function call case */
	else if(node->type == FUNC_CALL){
		AST_Node_Func_Call *temp_func_call = (struct AST_Node_Func_Call *) node;
		ast_print_node(node);
		if(temp_func_call->num_of_pars != 0){
			printf("Call parameters:\n");
			for(i = 0; i < temp_func_call->num_of_pars; i++){
				ast_traversal(temp_func_call->params[i]);
			}
		}
	}
	else if(node->type == CALL_PARAMS){
		AST_Node_Call_Params *temp_call_params = (struct AST_Node_Call_Params*) node;
		ast_print_node(node);
		if(temp_call_params->num_of_pars > 0){
			printf("Call Parameters:\n");
			for(i = 0; i < temp_call_params->num_of_pars; i++){
				ast_traversal(temp_call_params->params[i]);
			}
		}
	}
	/* function declarations case */
	else if(node->type == FUNC_DECLS){
		AST_Node_Func_Declarations *temp_func_declarations = (struct AST_Node_Func_Declarations *) node;	
		ast_print_node(node);
		for(i = 0; i < temp_func_declarations->func_declaration_count; i++){
			ast_traversal(temp_func_declarations->func_declarations[i]);
		}
	}
	/* function declaration case */
	else if(node->type == FUNC_DECL){
		AST_Node_Func_Decl *temp_func_decl = (struct AST_Node_Func_Decl *) node;
		ast_print_node(node);
		if(temp_func_decl->entry->num_of_pars != 0){
			printf("Parameters:\n");
			for(i = 0; i < temp_func_decl->entry->num_of_pars; i++){
				printf("Parameter %s of type %d\n", 
					temp_func_decl->entry->parameters[i].param_name,
					temp_func_decl->entry->parameters[i].par_type
				);
			}
		}
		if(temp_func_decl->declarations != NULL){
			printf("Function declarations:\n");
			ast_traversal(temp_func_decl->declarations);
		}
		if(temp_func_decl->statements != NULL){
			printf("Function statements:\n");
			ast_traversal(temp_func_decl->statements);
		}
		if(temp_func_decl->return_node != NULL){
			printf("Return node:\n");
			ast_traversal(temp_func_decl->return_node);
		}
	}
	/* parameter declarations case */
	else if(node->type == DECL_PARAMS){
		AST_Node_Decl_Params *temp_decl_params = (struct AST_Node_Decl_Params *) node;
		ast_print_node(node);
		printf("Call parameters:\n");
		for(i = 0; i < temp_decl_params->num_of_pars; i++){
			printf("Parameter %s of type %d\n", temp_decl_params->parameters[i].param_name, temp_decl_params->parameters[i].par_type);
		}		
	}
	/* return case */
	else if(node->type == RETURN_NODE){
		AST_Node_Return *temp_return = (struct AST_Node_Return *) node;
		ast_print_node(node);
		printf("Returning:\n");
		ast_traversal(temp_return->ret_val);
	}
	/* others */
	else{
		ast_print_node(node);
	}
}
