#include "../include/semantics.h"
#include <stdio.h>
#include <stdlib.h>

// line number
extern int yylineno;

/* flag variable that shows revisit in assignment expression */
int cont_revisit = 0; // 1: contains revisit, 0: not

// actual types are: INT_TYPE, REAL_TYPE, CHAR_TYPE

int get_result_type(int type_1, int type_2,
                    int op_type) { /* type check and result type */
    switch (op_type) {
    case NONE: /* type compatibility only, '1': compatible */
        // first type INT
        if (type_1 == INT_TYPE) {
            // second type INT or CHAR
            if (type_2 == INT_TYPE || type_2 == CHAR_TYPE) {
                return 1;
            } else {
                type_error(type_1, type_2, op_type);
            }
        }
        // first type REAL
        else if (type_1 == REAL_TYPE) {
            // second type INT, REAL or CHAR
            if (type_2 == INT_TYPE || type_2 == REAL_TYPE ||
                type_2 == CHAR_TYPE) {
                return 1;
            } else {
                type_error(type_1, type_2, op_type);
            }
        }
        // first type CHAR
        else if (type_1 == CHAR_TYPE) {
            // second type INT or CHAR
            if (type_2 == INT_TYPE || type_2 == CHAR_TYPE) {
                return 1;
            } else {
                type_error(type_1, type_2, op_type);
            }
        }
        break;
    /* ---------------------------------------------------------- */
    case ARITHM_OP: /* arithmetic operator */
        // first type INT
        if (type_1 == INT_TYPE) {
            // second type INT or CHAR
            if (type_2 == INT_TYPE || type_2 == CHAR_TYPE) {
                return INT_TYPE;
            }
            // second type REAL
            else if (type_2 == REAL_TYPE) {
                return REAL_TYPE;
            } else {
                type_error(type_1, type_2, op_type);
            }
        }
        // first type REAL
        else if (type_1 == REAL_TYPE) {
            // second type INT, REAL or CHAR
            if (type_2 == INT_TYPE || type_2 == REAL_TYPE ||
                type_2 == CHAR_TYPE) {
                return REAL_TYPE;
            } else {
                type_error(type_1, type_2, op_type);
            }
        }
        // first type CHAR
        else if (type_1 == CHAR_TYPE) {
            // second type INT or CHAR
            if (type_2 == INT_TYPE || type_2 == CHAR_TYPE) {
                return CHAR_TYPE;
            }
            // second type REAL
            else if (type_2 == REAL_TYPE) {
                return REAL_TYPE;
            } else {
                type_error(type_1, type_2, op_type);
            }
        } else {
            type_error(type_1, type_2, op_type);
        }
        break;
    /* ---------------------------------------------------------- */
    case INCR_OP: /* special case of INCR */
        // type INT
        if (type_1 == INT_TYPE) {
            return INT_TYPE;
        }
        // type REAL
        else if (type_1 == REAL_TYPE) {
            return REAL_TYPE;
        }
        // type CHAR
        else if (type_1 == CHAR_TYPE) {
            return CHAR_TYPE;
        } else {
            type_error(type_1, type_2, op_type);
        }
        break;
    /* ---------------------------------------------------------- */
    case BOOL_OP: /* Boolean operator */
        // first type INT
        if (type_1 == INT_TYPE) {
            // second type INT or CHAR
            if (type_2 == INT_TYPE || type_2 == CHAR_TYPE) {
                return INT_TYPE;
            } else {
                type_error(type_1, type_2, op_type);
            }
        }
        // first type CHAR
        else if (type_1 == CHAR_TYPE) {
            // second type INT or CHAR
            if (type_2 == INT_TYPE || type_2 == CHAR_TYPE) {
                return CHAR_TYPE;
            } else {
                type_error(type_1, type_2, op_type);
            }
        } else {
            type_error(type_1, type_2, op_type);
        }
        break;
    /* ---------------------------------------------------------- */
    case NOT_OP: /* special case of NOTOP */
        // type INT
        if (type_1 == INT_TYPE) {
            return INT_TYPE;
        }
        // type CHAR
        else if (type_1 == CHAR_TYPE) {
            return INT_TYPE;
        } else {
            type_error(type_1, type_2, op_type);
        }
        break;
    /* ---------------------------------------------------------- */
    case REL_OP: /* Relational operator */
        // first type INT
        if (type_1 == INT_TYPE) {
            // second type INT, REAL or CHAR
            if (type_2 == INT_TYPE || type_2 == REAL_TYPE ||
                type_2 == CHAR_TYPE) {
                return INT_TYPE;
            } else {
                type_error(type_1, type_2, op_type);
            }
        } else if (type_1 == REAL_TYPE) {
            // second type INT, REAL or CHAR
            if (type_2 == INT_TYPE || type_2 == REAL_TYPE ||
                type_2 == CHAR_TYPE) {
                return INT_TYPE;
            } else {
                type_error(type_1, type_2, op_type);
            }
        }
        // first type CHAR
        else if (type_1 == CHAR_TYPE) {
            // second type INT, REAL or CHAR
            if (type_2 == INT_TYPE || type_2 == REAL_TYPE ||
                type_2 == CHAR_TYPE) {
                return INT_TYPE;
            } else {
                type_error(type_1, type_2, op_type);
            }
        } else {
            type_error(type_1, type_2, op_type);
        }
        break;
    /* ---------------------------------------------------------- */
    case EQU_OP: /* Equality operator */
        // first type INT
        if (type_1 == INT_TYPE) {
            // second type INT or CHAR
            if (type_2 == INT_TYPE || type_2 == CHAR_TYPE) {
                return INT_TYPE;
            } else {
                type_error(type_1, type_2, op_type);
            }
        } else if (type_1 == REAL_TYPE) {
            // second type REAL
            if (type_2 == REAL_TYPE) {
                return INT_TYPE;
            } else {
                type_error(type_1, type_2, op_type);
            }
        }
        // first type CHAR
        else if (type_1 == CHAR_TYPE) {
            // second type INT or CHAR
            if (type_2 == INT_TYPE || type_2 == CHAR_TYPE) {
                return INT_TYPE;
            } else {
                type_error(type_1, type_2, op_type);
            }
        } else {
            type_error(type_1, type_2, op_type);
        }
        break;
    /* ---------------------------------------------------------- */
    default: /* wrong choice case */
        fprintf(stderr, "Error in operator selection!\n");
        exit(EXIT_FAILURE);
    }
}

void type_error(int type_1, int type_2, int op_type) { /* print type error */
    fprintf(stderr, "Type conflict between ");
    /* first type */
    if (type_1 == INT_TYPE)
        fprintf(stderr, "%s", "int");
    else if (type_1 == REAL_TYPE)
        fprintf(stderr, "%s", "real");
    else if (type_1 == CHAR_TYPE)
        fprintf(stderr, "%s", "char");
    else
        fprintf(stderr, "%s", "other");

    fprintf(stderr, " and ");

    /* second type */
    if (type_2 == INT_TYPE)
        fprintf(stderr, "%s", "int");
    else if (type_2 == REAL_TYPE)
        fprintf(stderr, "%s", "real");
    else if (type_2 == CHAR_TYPE)
        fprintf(stderr, "%s", "char");
    else
        fprintf(stderr, "%s", "other");

    /* operator */
    fprintf(stderr, " using op type ");
    switch (op_type) {
    case NONE:
        fprintf(stderr, "%s", "NONE");
        break;
    case ARITHM_OP:
        fprintf(stderr, "%s", "ARITHM_OP");
        break;
    case INCR_OP:
        fprintf(stderr, "%s", "INCR_OP");
        break;
    case BOOL_OP:
        fprintf(stderr, "%s", "BOOL_OP");
        break;
    case NOT_OP:
        fprintf(stderr, "%s", "NOT_OP");
        break;
    case REL_OP:
        fprintf(stderr, "%s", "REL_OP");
        break;
    case EQU_OP:
        fprintf(stderr, "%s", "EQU_OP");
        break;
    default:
        fprintf(stderr, "Error in operator selection!\n");
        exit(EXIT_FAILURE);
    }

    /* line */
    fprintf(stderr, " in line %d\n", yylineno);

    exit(EXIT_FAILURE);
}

int expression_data_type(AST_Node *node) {
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
    switch (node->type) {
    case ARITHM_NODE: /* arithmetic expression */
        temp_arithm = (AST_Node_Arithm *)node;

        /* set datatype again */
        temp_arithm->data_type = get_result_type(
            expression_data_type(
                temp_arithm->left), /* data type of left expression */
            expression_data_type(
                temp_arithm->right), /* data type of right expression */
            ARITHM_OP                /* operation type */
        );

        return temp_arithm->data_type;
        break;
    case INCR_NODE: /* special case of increment */
        temp_incr = (AST_Node_Incr *)node;
        return temp_incr->entry->st_type;
        break;
    case BOOL_NODE: /* boolean expression */
        temp_bool = (AST_Node_Bool *)node;

        /* set datatype again */
        if (temp_bool->op != NOT) { /* AND or OR */
            temp_bool->data_type = get_result_type(
                expression_data_type(
                    temp_bool->left), /* data type of left expression */
                expression_data_type(
                    temp_bool->right), /* data type of right expression */
                BOOL_OP                /* operation type */
            );
        } else { /* NOT */
            temp_bool->data_type = get_result_type(
                expression_data_type(
                    temp_bool->left), /* data type of left expression */
                UNDEF,                /* there is no right expression */
                NOT_OP                /* operation type */
            );
        }

        return temp_bool->data_type;
        break;
    case REL_NODE: /* relational expression */
        temp_rel = (AST_Node_Rel *)node;

        /* set datatype again */
        temp_rel->data_type = get_result_type(
            expression_data_type(
                temp_rel->left), /* data type of left expression  */
            expression_data_type(
                temp_rel->right), /* data type of right expression */
            REL_OP                /* operation type */
        );

        return temp_rel->data_type;
        break;
    case EQU_NODE: /* equality expression */
        temp_equ = (AST_Node_Equ *)node;

        /* set datatype again */
        temp_equ->data_type = get_result_type(
            expression_data_type(
                temp_equ->left), /* data type of left expression  */
            expression_data_type(
                temp_equ->right), /* data type of right expression */
            EQU_OP                /* operation type */
        );

        return temp_equ->data_type;
        break;
    case REF_NODE: /* identifier reference */
        temp_ref = (AST_Node_Ref *)node;
        /* if "simple" type */
        int type = temp_ref->entry->st_type;
        if (type == INT_TYPE || type == REAL_TYPE || type == CHAR_TYPE) {
            return temp_ref->entry->st_type;
        }
        /* if array or pointer */
        else {
            return temp_ref->entry->inf_type;
        }
        break;
    case CONST_NODE: /* constant */
        temp_const = (AST_Node_Const *)node;
        return temp_const->const_type; /* constant data type */
        break;
    case FUNC_CALL: /* function call */
        temp_func_call = (AST_Node_Func_Call *)node;

        /* check if it needs revisit */
        if (temp_func_call->entry->st_type == UNDEF) {
            if (temp_func_call->entry->inf_type == UNDEF) {
                cont_revisit = 1; /* contains revisit */
                return INT_TYPE;  /*   dummy return   */
            }
        }

        return temp_func_call->entry->inf_type; /* return type */
        break;
    default: /* wrong choice case */
        fprintf(stderr, "Error in AST node selection!\n");
        exit(EXIT_FAILURE);
    }
}