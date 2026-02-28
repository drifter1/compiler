#include "../include/ast.h"
#include "../include/semantics.h"
#include <stdlib.h>
#include <string.h>

extern int yylineno;

AST_Node *ast;

/* ------------------AST NODE MANAGEMENT-------------------- */
/* Program */
AST_Node *new_program_node(AST_Node *declarations, AST_Node *statements,
                           AST_Node *func_declarations) {

    // allocate memory
    AST_Node_Program *v = malloc(sizeof(AST_Node_Program));

    // set node type
    v->type = PROGRAM_NODE;

    // set entries
    v->declarations = declarations;
    v->statements = statements;
    v->func_declarations = func_declarations;

    // return type-casted result
    return (struct AST_Node *)v;
}

/* Declarations */
AST_Node *new_declarations_node(AST_Node **declarations, int declaration_count,
                                AST_Node *declaration) {
    // allocate memory
    AST_Node_Declarations *v = malloc(sizeof(AST_Node_Declarations));

    // set node type
    v->type = DECLARATIONS;

    // first declaration
    if (declarations == NULL) {
        declarations = (AST_Node **)malloc(sizeof(AST_Node *));
        declarations[0] = declaration;
        declaration_count = 1;
    }
    // add new declaration
    else {
        declarations = (AST_Node **)realloc(
            declarations, (declaration_count + 1) * sizeof(AST_Node *));
        declarations[declaration_count] = declaration;
        declaration_count++;
    }

    // set entries
    v->declarations = declarations;
    v->declaration_count = declaration_count;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_decl_node(int data_type, list_t **names, int names_count) {
    // allocate memory
    AST_Node_Decl *v = malloc(sizeof(AST_Node_Decl));

    // set entries
    v->type = DECL_NODE;
    v->data_type = data_type;
    v->names = names;
    v->names_count = names_count;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_const_node(int const_type, Value val) {
    // allocate memory
    AST_Node_Const *v = malloc(sizeof(AST_Node_Const));

    // set entries
    v->type = CONST_NODE;
    v->const_type = const_type;
    v->val = val;

    // return type-casted result
    return (struct AST_Node *)v;
}

/* Statements */

AST_Node *new_statements_node(AST_Node **statements, int statement_count,
                              AST_Node *statement) {
    // allocate memory
    AST_Node_Statements *v = malloc(sizeof(AST_Node_Statements));

    // set node type
    v->type = STATEMENTS;

    // first statement
    if (statements == NULL) {
        statements = (AST_Node **)malloc(sizeof(AST_Node *));
        statements[0] = statement;
        statement_count = 1;
    }
    // add new statement
    else {
        statements = (AST_Node **)realloc(statements, (statement_count + 1) *
                                                          sizeof(AST_Node *));
        statements[statement_count] = statement;
        statement_count++;
    }

    // set entries
    v->statements = statements;
    v->statement_count = statement_count;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_if_node(AST_Node *condition, AST_Node *if_branch,
                          AST_Node **elsif_branches, int elseif_count,
                          AST_Node *else_branch) {
    // allocate memory
    AST_Node_If *v = malloc(sizeof(AST_Node_If));

    // set entries
    v->type = IF_NODE;
    v->condition = condition;
    v->if_branch = if_branch;
    v->elsif_branches = elsif_branches;
    v->elseif_count = elseif_count;
    v->else_branch = else_branch;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_elsif_node(AST_Node *condition, AST_Node *elsif_branch) {
    // allocate memory
    AST_Node_Elsif *v = malloc(sizeof(AST_Node_Elsif));

    // set entries
    v->type = ELSIF_NODE;
    v->condition = condition;
    v->elsif_branch = elsif_branch;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_for_node(AST_Node *initialize, AST_Node *condition,
                           AST_Node *increment, AST_Node *for_branch) {
    // allocate memory
    AST_Node_For *v = malloc(sizeof(AST_Node_For));

    // set entries
    v->type = FOR_NODE;
    v->initialize = initialize;
    v->condition = condition;
    v->increment = increment;
    v->for_branch = for_branch;

    // return type-casted result
    return (struct AST_Node *)v;
}

void set_loop_counter(AST_Node *node) {
    /* type-cast to for node */
    AST_Node_For *for_node = (AST_Node_For *)node;

    /* find the counter */
    AST_Node_Assign *assign_node = (AST_Node_Assign *)for_node->initialize;
    for_node->counter = assign_node->entry;

    /* check if the same one occurs in increment! */
    AST_Node_Incr *incr_node = (AST_Node_Incr *)for_node->increment;
    if (strcmp(incr_node->entry->st_name, assign_node->entry->st_name)) {
        fprintf(stderr,
                "Semantic error at line %d. Variable used in init and incr of "
                "for are not the same\n",
                yylineno);
        exit(EXIT_FAILURE);
    }

    /* type-cast back to AST_Node */
    node = (AST_Node *)for_node;
}

AST_Node *new_ast_while_node(AST_Node *condition, AST_Node *while_branch) {
    // allocate memory
    AST_Node_While *v = malloc(sizeof(AST_Node_While));

    // set entries
    v->type = WHILE_NODE;
    v->condition = condition;
    v->while_branch = while_branch;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_assign_node(list_t *entry, int ref, AST_Node *assign_val) {
    // allocate memory
    AST_Node_Assign *v = malloc(sizeof(AST_Node_Assign));

    // set entries
    v->type = ASSIGN_NODE;
    v->entry = entry;
    v->ref = ref;
    v->assign_val = assign_val;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_simple_node(int statement_type) {
    // allocate memory
    AST_Node_Simple *v = malloc(sizeof(AST_Node_Simple));

    // set entries
    v->type = SIMPLE_NODE;
    v->statement_type = statement_type;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_incr_node(list_t *entry, int incr_type, int pf_type) {
    // allocate memory
    AST_Node_Incr *v = malloc(sizeof(AST_Node_Incr));

    // set entries
    v->type = INCR_NODE;
    v->entry = entry;
    v->incr_type = incr_type;
    v->pf_type = pf_type;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_func_call_node(list_t *entry, AST_Node **params,
                                 int num_of_pars) {
    // allocate memory
    AST_Node_Func_Call *v = malloc(sizeof(AST_Node_Func_Call));

    // set entries
    v->type = FUNC_CALL;
    v->entry = entry;
    v->params = params;
    v->num_of_pars = num_of_pars;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_call_params_node(AST_Node **params, int num_of_pars,
                                   AST_Node *param) {
    // allocate memory
    AST_Node_Call_Params *v = malloc(sizeof(AST_Node_Call_Params));

    // set type
    v->type = CALL_PARAMS;

    // first parameter
    if (params == NULL) {
        params = (AST_Node **)malloc(sizeof(AST_Node *));
        params[0] = param;
        num_of_pars = 1;
    }
    // add new parameter
    else {
        params = (AST_Node **)realloc(params,
                                      (num_of_pars + 1) * sizeof(AST_Node *));
        params[num_of_pars] = param;
        num_of_pars++;
    }

    // set entries
    v->params = params;
    v->num_of_pars = num_of_pars;

    // return type-casted result
    return (struct AST_Node *)v;
}

/* Expressions */

AST_Node *new_ast_arithm_node(enum Arithm_op op, AST_Node *left,
                              AST_Node *right) {
    // allocate memory
    AST_Node_Arithm *v = malloc(sizeof(AST_Node_Arithm));

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
    return (struct AST_Node *)v;
}

AST_Node *new_ast_bool_node(enum Bool_op op, AST_Node *left, AST_Node *right) {
    // allocate memory
    AST_Node_Bool *v = malloc(sizeof(AST_Node_Bool));

    // set entries
    v->type = BOOL_NODE;
    v->op = op;
    v->left = left;
    v->right = right;

    // set data type
    if (v->op != NOT) { /* AND or OR */
        v->data_type = get_result_type(
            expression_data_type(left),  /* data type of left expression */
            expression_data_type(right), /* data type of right expression */
            BOOL_OP                      /* operation type */
        );
    } else { /* NOT */
        v->data_type = get_result_type(
            expression_data_type(left), /* data type of left expression */
            UNDEF,                      /* there is no right expression */
            NOT_OP                      /* operation type */
        );
    }

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_rel_node(enum Rel_op op, AST_Node *left, AST_Node *right) {
    // allocate memory
    AST_Node_Rel *v = malloc(sizeof(AST_Node_Rel));

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
    return (struct AST_Node *)v;
}

AST_Node *new_ast_equ_node(enum Equ_op op, AST_Node *left, AST_Node *right) {
    // allocate memory
    AST_Node_Equ *v = malloc(sizeof(AST_Node_Equ));

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
    return (struct AST_Node *)v;
}

AST_Node *new_ast_ref_node(list_t *entry, int ref) {
    // allocate memory
    AST_Node_Ref *v = malloc(sizeof(AST_Node_Ref));

    // set entries
    v->type = REF_NODE;
    v->entry = entry;
    v->ref = ref;

    // return type-casted result
    return (struct AST_Node *)v;
}

/* Functions */
AST_Node *new_func_declarations_node(AST_Node **func_declarations,
                                     int func_declaration_count,
                                     AST_Node *func_declaration) {
    // allocate memory
    AST_Node_Func_Declarations *v = malloc(sizeof(AST_Node_Func_Declarations));

    // set node type
    v->type = FUNC_DECLS;

    // first declaration
    if (func_declarations == NULL) {
        func_declarations = (AST_Node **)malloc(sizeof(AST_Node *));
        func_declarations[0] = func_declaration;
        func_declaration_count = 1;
    }
    // add new declaration
    else {
        func_declarations = (AST_Node **)realloc(func_declarations,
                                                 (func_declaration_count + 1) *
                                                     sizeof(AST_Node *));
        func_declarations[func_declaration_count] = func_declaration;
        func_declaration_count++;
    }

    // set entries
    v->func_declarations = func_declarations;
    v->func_declaration_count = func_declaration_count;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_func_decl_node(int ret_type, int pointer, list_t *entry) {
    // allocate memory
    AST_Node_Func_Decl *v = malloc(sizeof(AST_Node_Func_Decl));

    // set entries
    v->type = FUNC_DECL;
    v->ret_type = ret_type;
    v->pointer = pointer;
    v->entry = entry;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_ret_type_node(int ret_type, int pointer) {
    // allocate memory
    AST_Node_Ret_Type *v = malloc(sizeof(AST_Node_Ret_Type));

    // set entries
    v->type = RET_TYPE;
    v->ret_type = ret_type;
    v->pointer = pointer;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_decl_params_node(Param *parameters, int num_of_pars,
                                   Param param) {
    // allocate memory
    AST_Node_Decl_Params *v = malloc(sizeof(AST_Node_Decl_Params));

    // set node type
    v->type = DECL_PARAMS;

    // first declaration
    if (parameters == NULL) {
        parameters = (Param *)malloc(sizeof(Param));
        parameters[0] = param;
        num_of_pars = 1;
    }
    // add new declaration
    else {
        parameters =
            (Param *)realloc(parameters, (num_of_pars + 1) * sizeof(Param));
        parameters[num_of_pars] = param;
        num_of_pars++;
    }

    // set entries
    v->parameters = parameters;
    v->num_of_pars = num_of_pars;

    // return type-casted result
    return (struct AST_Node *)v;
}

AST_Node *new_ast_return_node(int ret_type, AST_Node *ret_val) {
    // allocate memory
    AST_Node_Return *v = malloc(sizeof(AST_Node_Return));

    // set entries
    v->type = RETURN_NODE;
    v->ret_type = ret_type;
    v->ret_val = ret_val;

    // return type-casted result
    return (struct AST_Node *)v;
}