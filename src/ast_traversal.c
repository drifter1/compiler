#include "../include/ast.h"
#include "../include/semantics.h"
#include <stdlib.h>

/* Tree Traversal */

void ast_print_node(AST_Node *node) {
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

    switch (node->type) {
    case BASIC_NODE:
        printf("Basic Node\n");
        break;
    case DECLARATIONS:
        temp_declarations = (struct AST_Node_Declarations *)node;
        printf("Declarations Node with %d declarations\n",
               temp_declarations->declaration_count);
        break;
    case DECL_NODE:
        temp_decl = (struct AST_Node_Decl *)node;
        printf("Declaration Node of data-type %d for %d names\n",
               temp_decl->data_type, temp_decl->names_count);
        break;
    case CONST_NODE:
        temp_const = (struct AST_Node_Const *)node;
        printf("Constant Node of const-type %d with value ",
               temp_const->const_type);
        switch (temp_const->const_type) {
        case INT_TYPE:
            printf("%d\n", temp_const->val.ival);
            break;
        case REAL_TYPE:
            printf("%.2f\n", temp_const->val.fval);
            break;
        case CHAR_TYPE:
            printf("%c\n", temp_const->val.cval);
            break;
        case STR_TYPE:
            printf("%s\n", temp_const->val.sval);
            break;
        }
        break;
    case STATEMENTS:
        temp_statements = (struct AST_Node_Statements *)node;
        printf("Statements Node with %d statements\n",
               temp_statements->statement_count);
        break;
    case IF_NODE:
        temp_if = (struct AST_Node_If *)node;
        printf("If Node with %d elseifs and ", temp_if->elseif_count);
        if (temp_if->else_branch == NULL) {
            printf("no else\n");
        } else {
            printf("else\n");
        }
        break;
    case ELSIF_NODE:
        printf("Elsif Node\n");
        break;
    case FOR_NODE:
        temp_for = (struct AST_Node_For *)node;
        printf("For Node with loop counter %s\n", temp_for->counter->st_name);
        break;
    case WHILE_NODE:
        printf("While Node\n");
        break;
    case ASSIGN_NODE:
        temp_assign = (struct AST_Node_Assign *)node;
        printf("Assign Node of entry %s\n", temp_assign->entry->st_name);
        break;
    case SIMPLE_NODE:
        temp_simple = (struct AST_Node_Simple *)node;
        printf("Simple Node of statement %d\n", temp_simple->statement_type);
        break;
    case INCR_NODE:
        temp_incr = (struct AST_Node_Incr *)node;
        printf("Increment Node of entry %s being %d %d\n",
               temp_incr->entry->st_name, temp_incr->incr_type,
               temp_incr->pf_type);
        break;
    case FUNC_CALL:
        temp_func_call = (struct AST_Node_Func_Call *)node;
        printf("Function Call Node of %s with %d parameters\n",
               temp_func_call->entry->st_name, temp_func_call->num_of_pars);
        break;
    case CALL_PARAMS:
        temp_call_params = (struct AST_Node_Call_Params *)node;
        printf("Function Call Parameters Node with %d parameters\n",
               temp_call_params->num_of_pars);
        break;
    case ARITHM_NODE:
        temp_arithm = (struct AST_Node_Arithm *)node;
        printf("Arithmetic Node of operator %d with result type %d\n",
               temp_arithm->op, temp_arithm->data_type);
        break;
    case BOOL_NODE:
        temp_bool = (struct AST_Node_Bool *)node;
        printf("Boolean Node of operator %d\n", temp_bool->op);
        break;
    case REL_NODE:
        temp_rel = (struct AST_Node_Rel *)node;
        printf("Relational Node of operator %d\n", temp_rel->op);
        break;
    case EQU_NODE:
        temp_equ = (struct AST_Node_Equ *)node;
        printf("Equality Node of operator %d\n", temp_equ->op);
        break;
    case REF_NODE:
        temp_ref = (struct AST_Node_Ref *)node;
        printf("Reference Node of entry %s\n", temp_ref->entry->st_name);
        break;
    case FUNC_DECLS:
        temp_func_declarations = (struct AST_Node_Func_Declarations *)node;
        printf("Function Declarations Node with %d function declarations\n",
               temp_func_declarations->func_declaration_count);
        break;
    case FUNC_DECL:
        temp_func_decl = (struct AST_Node_Func_Decl *)node;
        printf("Function Declaration Node of %s with ret_type %d and %d "
               "parameters\n",
               temp_func_decl->entry->st_name, temp_func_decl->ret_type,
               temp_func_decl->entry->num_of_pars);
        break;
    case RET_TYPE:
        temp_ret_type = (struct AST_Node_Ret_Type *)node;
        printf("Return type %d which is ", temp_ret_type->ret_type);
        if (temp_ret_type->pointer) {
            printf("a pointer\n");
        } else {
            printf("not a pointer\n");
        }
        break;
    case DECL_PARAMS:
        temp_decl_params = (struct AST_Node_Decl_Params *)node;
        printf("Function declaration parameters node of %d parameters\n",
               temp_decl_params->num_of_pars);
        break;
    case RETURN_NODE:
        temp_return = (struct AST_Node_Return *)node;
        printf("Return Node of ret_type %d\n", temp_return->ret_type);
        break;
    default: /* wrong choice case */
        fprintf(stderr, "Error in AST node selection!\n");
        exit(EXIT_FAILURE);
    }
}

void ast_traversal(AST_Node *node) {
    int i;

    /* check if empty */
    if (node == NULL) {
        return;
    }

    /* left and right child cases */
    if (node->type == BASIC_NODE || node->type == ARITHM_NODE ||
        node->type == BOOL_NODE || node->type == REL_NODE ||
        node->type == EQU_NODE) {
        // ast_traversal(node->left);
        // ast_traversal(node->right);
        ast_print_node(node); // postfix
    }
    /* declarations case */
    else if (node->type == DECLARATIONS) {
        AST_Node_Declarations *temp_declarations =
            (struct AST_Node_Declarations *)node;
        ast_print_node(node);
        for (i = 0; i < temp_declarations->declaration_count; i++) {
            ast_traversal(temp_declarations->declarations[i]);
        }
    }
    /* statements case */
    else if (node->type == STATEMENTS) {
        AST_Node_Statements *temp_statements =
            (struct AST_Node_Statements *)node;
        ast_print_node(node);
        for (i = 0; i < temp_statements->statement_count; i++) {
            ast_traversal(temp_statements->statements[i]);
        }
    }
    /* the if case */
    else if (node->type == IF_NODE) {
        AST_Node_If *temp_if = (struct AST_Node_If *)node;
        ast_print_node(node);

        printf("Condition:\n");
        ast_traversal(temp_if->condition);

        printf("If branch:\n");
        ast_traversal(temp_if->if_branch);

        if (temp_if->elseif_count > 0) {
            printf("Else if branches:\n");
            for (i = 0; i < temp_if->elseif_count; i++) {
                printf("Else if branch%d:\n", i);
                ast_traversal(temp_if->elsif_branches[i]);
            }
        }

        if (temp_if->else_branch != NULL) {
            printf("Else branch:\n");
            ast_traversal(temp_if->else_branch);
        }
    }
    /* the else if case */
    else if (node->type == ELSIF_NODE) {
        AST_Node_Elsif *temp_elsif = (struct AST_Node_Elsif *)node;
        ast_print_node(node);
        ast_traversal(temp_elsif->condition);
        ast_traversal(temp_elsif->elsif_branch);
    }
    /* for case */
    else if (node->type == FOR_NODE) {
        AST_Node_For *temp_for = (struct AST_Node_For *)node;
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
    else if (node->type == WHILE_NODE) {
        AST_Node_While *temp_while = (struct AST_Node_While *)node;
        ast_print_node(node);
        printf("Condition:\n");
        ast_traversal(temp_while->condition);
        printf("While branch:\n");
        ast_traversal(temp_while->while_branch);
    }
    /* assign case */
    else if (node->type == ASSIGN_NODE) {
        AST_Node_Assign *temp_assign = (struct AST_Node_Assign *)node;
        ast_print_node(node);
        printf("Assigning:\n");
        ast_traversal(temp_assign->assign_val);
    }
    /* function call case */
    else if (node->type == FUNC_CALL) {
        AST_Node_Func_Call *temp_func_call = (struct AST_Node_Func_Call *)node;
        ast_print_node(node);
        if (temp_func_call->num_of_pars != 0) {
            printf("Call parameters:\n");
            for (i = 0; i < temp_func_call->num_of_pars; i++) {
                ast_traversal(temp_func_call->params[i]);
            }
        }
    } else if (node->type == CALL_PARAMS) {
        AST_Node_Call_Params *temp_call_params =
            (struct AST_Node_Call_Params *)node;
        ast_print_node(node);
        if (temp_call_params->num_of_pars > 0) {
            printf("Call Parameters:\n");
            for (i = 0; i < temp_call_params->num_of_pars; i++) {
                ast_traversal(temp_call_params->params[i]);
            }
        }
    }
    /* function declarations case */
    else if (node->type == FUNC_DECLS) {
        AST_Node_Func_Declarations *temp_func_declarations =
            (struct AST_Node_Func_Declarations *)node;
        ast_print_node(node);
        for (i = 0; i < temp_func_declarations->func_declaration_count; i++) {
            ast_traversal(temp_func_declarations->func_declarations[i]);
        }
    }
    /* function declaration case */
    else if (node->type == FUNC_DECL) {
        AST_Node_Func_Decl *temp_func_decl = (struct AST_Node_Func_Decl *)node;
        ast_print_node(node);
        if (temp_func_decl->entry->num_of_pars != 0) {
            printf("Parameters:\n");
            for (i = 0; i < temp_func_decl->entry->num_of_pars; i++) {
                printf("Parameter %s of type %d\n",
                       temp_func_decl->entry->parameters[i].param_name,
                       temp_func_decl->entry->parameters[i].par_type);
            }
        }
        if (temp_func_decl->declarations != NULL) {
            printf("Function declarations:\n");
            ast_traversal(temp_func_decl->declarations);
        }
        if (temp_func_decl->statements != NULL) {
            printf("Function statements:\n");
            ast_traversal(temp_func_decl->statements);
        }
        if (temp_func_decl->return_node != NULL) {
            printf("Return node:\n");
            ast_traversal(temp_func_decl->return_node);
        }
    }
    /* parameter declarations case */
    else if (node->type == DECL_PARAMS) {
        AST_Node_Decl_Params *temp_decl_params =
            (struct AST_Node_Decl_Params *)node;
        ast_print_node(node);
        printf("Call parameters:\n");
        for (i = 0; i < temp_decl_params->num_of_pars; i++) {
            printf("Parameter %s of type %d\n",
                   temp_decl_params->parameters[i].param_name,
                   temp_decl_params->parameters[i].par_type);
        }
    }
    /* return case */
    else if (node->type == RETURN_NODE) {
        AST_Node_Return *temp_return = (struct AST_Node_Return *)node;
        ast_print_node(node);
        printf("Returning:\n");
        ast_traversal(temp_return->ret_val);
    }
    /* others */
    else {
        ast_print_node(node);
    }
}