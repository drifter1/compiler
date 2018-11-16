#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

AST_Node *new_ast_if_node(AST_Node *condition, AST_Node *if_branch, AST_Node **elsif_branches, int elseif_count, AST_Node *else_branch){
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

AST_Node *new_ast_assign_node(list_t *entry, AST_Node *assign_val){
	// allocate memory
	AST_Node_Assign *v = malloc (sizeof (AST_Node_Assign));
	
	// set entries
	v->type = ASSIGN_NODE;
	v->entry = entry;
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

/* Expressions */

AST_Node *new_ast_arithm_node(enum Arithm_op op, AST_Node *left, AST_Node *right){
	// allocate memory
	AST_Node_Arithm *v = malloc (sizeof (AST_Node_Arithm));
	
	// set entries
	v->type = ARITHM_NODE;
	v->op = op;
	v->left = left;
	v->right = right;
	
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
	
	// return type-casted result
	return (struct AST_Node *) v;	
}

/* Functions */

AST_Node *new_ast_func_decl_node(int ret_type, list_t *entry){
	// allocate memory
	AST_Node_Func_Decl *v = malloc (sizeof (AST_Node_Func_Decl));
	
	// set entries
	v->type = FUNC_DECL;
	v->ret_type = ret_type;
	v->entry = entry;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

AST_Node *new_ast_return_node(int ret_type, AST_Node *ret_val){
	// allocate memory
	AST_Node_Return *v = malloc (sizeof (AST_Node_Return));
	
	// set entries
	v->type = FUNC_DECL;
	v->ret_type = ret_type;
	v->ret_val = ret_val;
	
	// return type-casted result
	return (struct AST_Node *) v;
}

/* Tree Traversal */

void ast_print_node(AST_Node *node){
	/* temp nodes */
	AST_Node_Decl *temp_decl;
	AST_Node_Const *temp_const;
	AST_Node_If *temp_if;
	AST_Node_Assign *temp_assign;
	AST_Node_Simple *temp_simple;
	AST_Node_Incr *temp_incr;
	AST_Node_Func_Call *temp_func_call;
	AST_Node_Arithm *temp_arithm;
	AST_Node_Bool *temp_bool;
	AST_Node_Rel *temp_rel;
	AST_Node_Equ *temp_equ;
	AST_Node_Func_Decl *temp_func_decl;
	AST_Node_Return *temp_return;
	
	switch(node->type){
		case BASIC_NODE:
			printf("Basic Node\n");
			break;
		case DECL_NODE:
			temp_decl = (struct AST_Node_Decl *) node;
			printf("Declaration Node of data-type %d for %d names\n",
				temp_decl->data_type, temp_decl->names_count);
			break;
		case CONST_NODE:
			temp_const = (struct AST_Node_Const *) node;
			printf("Constant Node of const-type %d\n", temp_const->const_type);
			break;
		case IF_NODE:
			temp_if = (struct AST_Node_If *) node;
			printf("If Node with %d elseifs\n", temp_if->elseif_count);
			break;
		case ELSIF_NODE:
			printf("Elsif Node\n");
			break;
		case FOR_NODE:
			printf("For Node\n");
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
			printf("Function Call Node with %d parameters\n", temp_func_call->num_of_pars);
			break;
		case ARITHM_NODE:
			temp_arithm = (struct AST_Node_Arithm *) node;
			printf("Arithmetic Node of operator %d\n", temp_arithm->op);
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
		case FUNC_DECL:
			temp_func_decl = (struct AST_Node_Func_Decl *) node;
			printf("Function Declaration Node of %s with ret_type %d\n", temp_func_decl->entry->st_name, temp_func_decl->ret_type);
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
		ast_traversal(node->left);
		ast_traversal(node->right);
		ast_print_node(node); // postfix
	}
	/* the if case */
	else if(node->type == IF_NODE){
		AST_Node_If *temp_if = (struct AST_Node_If *) node;
		ast_traversal(temp_if->condition);
		ast_traversal(temp_if->if_branch);
		for(i = 0; i < temp_if->elseif_count; i++){
			ast_traversal(temp_if->elsif_branches[i]);
		}
		ast_traversal(temp_if->else_branch);
		ast_print_node(node);
	}
	/* the else if case */ 
	else if(node->type == ELSIF_NODE){
		AST_Node_Elsif *temp_elsif = (struct AST_Node_Elsif *) node;
		ast_traversal(temp_elsif->condition);
		ast_traversal(temp_elsif->elsif_branch);
		ast_print_node(node);
	}
	/* for case */
	else if(node->type == FOR_NODE){
		AST_Node_For *temp_for = (struct AST_Node_For *) node;
		ast_traversal(temp_for->condition);
		ast_traversal(temp_for->for_branch);
		ast_print_node(node);
	}
	/* while case */
	else if(node->type == WHILE_NODE){
		AST_Node_While *temp_while = (struct AST_Node_While *) node;
		ast_traversal(temp_while->condition);
		ast_traversal(temp_while->while_branch);
		ast_print_node(node);
	}
	/* assign case */
	else if(node->type == ASSIGN_NODE){
		AST_Node_Assign *temp_assign = (struct AST_Node_Assign *) node;
		ast_traversal(temp_assign->assign_val);
		ast_print_node(node);
	}
	/* function call case */
	else if(node->type == FUNC_CALL){
		AST_Node_Func_Call *temp_func_call = (struct AST_Node_Func_Call *) node;
		for(i = 0; i < temp_func_call->num_of_pars; i++){
			ast_traversal(temp_func_call->params[i]);
		}
		ast_print_node(node);
	}
	/* return case */
	else if(node->type == RETURN_NODE){
		AST_Node_Return *temp_return = (struct AST_Node_Return *) node;
		ast_traversal(temp_return->ret_val);
		ast_print_node(node);
	}
	/* others */
	else{
		ast_print_node(node);
	}
}
