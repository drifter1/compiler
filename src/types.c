#include "../include/types.h"

/* -----------------HELPER FUNCTIONS----------------- */

char *data_type_to_string(data_type d_type) {
    switch (d_type) {
    case UNDEF_TYPE:
        return "undef";
        break;
    case INT_TYPE:
        return "int";
        break;
    case CHAR_TYPE:
        return "char";
        break;
    case FLOAT_TYPE:
        return "float";
        break;
    case DOUBLE_TYPE:
        return "double";
        break;
    case VOID_TYPE:
        return "void";
    }
    return "_error";
}

char *operator_type_to_string(operator_type op_type) {
    switch (op_type) {
    case NO_OP:
        return "no_op";
        break;
    case ASSIGN:
        return "assign (=)";
        break;
    case INC:
        return "inc (++)";
        break;
    case DEC:
        return "dec (--)";
        break;
    case PRE_INC:
        return "pre_inc (++a)";
        break;
    case PRE_DEC:
        return "pre_dec (--a)";
        break;
    case POST_INC:
        return "post_inc (a++)";
        break;
    case POST_DEC:
        return "post_dec (a--)";
        break;
    case ADD:
        return "add (+)";
        break;
    case SUB:
        return "sub (-)";
        break;
    case MUL:
        return "mul (*)";
        break;
    case DIV:
        return "div (/)";
        break;
    case REM:
        return "rem (%%)";
        break;
    case UNARY_PLUS:
        return "unary_plus (+a)";
        break;
    case UNARY_MINUS:
        return "unary_minus (-a)";
        break;
    case OR:
        return "or (||)";
        break;
    case AND:
        return "and (&&)";
        break;
    case NOT:
        return "not (!)";
        break;
    case EQUAL:
        return "equal (==)";
        break;
    case NOT_EQUAL:
        return "not_equal (!=)";
        break;
    case GREATER:
        return "greater (>)";
        break;
    case LESS:
        return "less (<)";
        break;
    case GREATER_EQUAL:
        return "greater_equal (>=)";
        break;
    case LESS_EQUAL:
        return "less_equal (<=)";
    }
    return "_error";
}

char *jump_type_to_string(jump_type j_type) {
    switch (j_type) {
    case CONTINUE:
        return "continue";
        break;
    case BREAK:
        return "break";
    }
    return "_error";
}

char *print_type_to_string(print_type p_type) {
    switch (p_type) {
    case EXPRESSION:
        return "expression";
        break;
    case STRING:
        return "string";
    }
    return "_error";
}