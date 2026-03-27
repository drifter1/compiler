#include "../include/types.h"

/* ------------------TYPE PROMOTION------------------ */

const data_type type_promotion_matrix[6][6] = {
    /* UNDEF_TYPE */
    {UNDEF_TYPE, UNDEF_TYPE, UNDEF_TYPE, UNDEF_TYPE, UNDEF_TYPE, UNDEF_TYPE},
    /* INT_TYPE */
    {UNDEF_TYPE, INT_TYPE, INT_TYPE, FLOAT_TYPE, DOUBLE_TYPE, UNDEF_TYPE},
    /* CHAR_TYPE */
    {UNDEF_TYPE, INT_TYPE, INT_TYPE, FLOAT_TYPE, DOUBLE_TYPE, UNDEF_TYPE},
    /* FLOAT_TYPE */
    {UNDEF_TYPE, FLOAT_TYPE, FLOAT_TYPE, FLOAT_TYPE, DOUBLE_TYPE, UNDEF_TYPE},
    /* DOUBLE_TYPE */
    {UNDEF_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE,
     UNDEF_TYPE},
    /* VOID_TYPE */
    {UNDEF_TYPE, UNDEF_TYPE, UNDEF_TYPE, UNDEF_TYPE, UNDEF_TYPE, UNDEF_TYPE}};

data_type promote_data_type(data_type origin_type, data_type target_type) {
    /* Guard against invalid type indices */
    if (origin_type < UNDEF_TYPE || origin_type > VOID_TYPE ||
        target_type < UNDEF_TYPE || target_type > VOID_TYPE) {
        return UNDEF_TYPE;
    }
    return type_promotion_matrix[origin_type][target_type];
}

/* ------------------OPERATOR RESULT----------------- */

data_type get_op_result_type(operator_type op_type, data_type left_type,
                             data_type right_type) {

    // right_type is left unused for increment/decrement and unary operations
    // both left_type and right_type are left unused for NO_OP, assignment,
    // logical and relational operations

    switch (op_type) {
    /* ------------- No Operation ------------ */
    case NO_OP:
        return UNDEF_TYPE;
    /* -------------- Assignment ------------- */
    case ASSIGN:
        /* The value returned by an assignment is the left-hand side */
        return left_type;
    /* -------- Increment / Decrement -------- */
    case INC:
    case DEC:
    case PRE_INC:
    case PRE_DEC:
    case POST_INC:
    case POST_DEC:
        return left_type;
    /* -------------- Arithmetic ------------- */
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case REM:
        return promote_data_type(left_type, right_type);
    /* ---------------- Unary ---------------- */
    case UNARY_PLUS:
    case UNARY_MINUS:
        return left_type;
    /* --------------- Logical --------------- */
    case OR:
    case AND:
    case NOT:
        return INT_TYPE;
    /* -------------- Relational ------------- */
    case EQUAL:
    case NOT_EQUAL:
    case GREATER:
    case LESS:
    case GREATER_EQUAL:
    case LESS_EQUAL:
        return INT_TYPE;
    }

    return UNDEF_TYPE;
}

/* -----------------DISPLAY FUNCTIONS---------------- */

char *data_type_to_string(data_type d_type) {
    switch (d_type) {
    case UNDEF_TYPE:
        return "undef";
    case INT_TYPE:
        return "int";
    case CHAR_TYPE:
        return "char";
    case FLOAT_TYPE:
        return "float";
    case DOUBLE_TYPE:
        return "double";
    case VOID_TYPE:
        return "void";
    }
    return "_error";
}

char *operator_type_to_string(operator_type op_type) {
    switch (op_type) {
    case NO_OP:
        return "no_op";
    case ASSIGN:
        return "assign (=)";
    case INC:
        return "inc (++)";
    case DEC:
        return "dec (--)";
    case PRE_INC:
        return "pre_inc (++a)";
    case PRE_DEC:
        return "pre_dec (--a)";
    case POST_INC:
        return "post_inc (a++)";
    case POST_DEC:
        return "post_dec (a--)";
    case ADD:
        return "add (+)";
    case SUB:
        return "sub (-)";
    case MUL:
        return "mul (*)";
    case DIV:
        return "div (/)";
    case REM:
        return "rem (%%)";
    case UNARY_PLUS:
        return "unary_plus (+a)";
    case UNARY_MINUS:
        return "unary_minus (-a)";
    case OR:
        return "or (||)";
    case AND:
        return "and (&&)";
    case NOT:
        return "not (!)";
    case EQUAL:
        return "equal (==)";
    case NOT_EQUAL:
        return "not_equal (!=)";
    case GREATER:
        return "greater (>)";
    case LESS:
        return "less (<)";
    case GREATER_EQUAL:
        return "greater_equal (>=)";
    case LESS_EQUAL:
        return "less_equal (<=)";
    }
    return "_error";
}

char *jump_type_to_string(jump_type j_type) {
    switch (j_type) {
    case CONTINUE:
        return "continue";
    case BREAK:
        return "break";
    }
    return "_error";
}

char *print_type_to_string(print_type p_type) {
    switch (p_type) {
    case EXPRESSION:
        return "expression";
    case STRING:
        return "string";
    }
    return "_error";
}