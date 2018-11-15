#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ast node management
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

AST_Node *new_ast_decl_node(int data_type, list_t **names){
	// allocate memory
	AST_Node_Decl *v = malloc (sizeof (AST_Node_Decl));
	
	// set entries
	v->type = DECL_NODE;
	v->data_type = data_type;
	v->names = names;
	
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

/* ... */
