#include "../include/tac.h"
#include <stdio.h>
#include <stdlib.h>

/* --------------------TAC LIST STRUCTURE------------------- */

tac_list *tl;

/* ----------------------MAIN FUNCTIONS--------------------- */

tac tac_create(op_code op, operand result, operand arg1, operand arg2) {
    tac t = {op, result, arg1, arg2};
    return t;
}

void tac_print(FILE *of, tac t) {
    const char *op_str = op_code_to_string(t.op);
    const char *result_str = operand_to_string(t.result);
    const char *arg1_str = operand_to_string(t.arg1);
    const char *arg2_str = operand_to_string(t.arg2);

    switch (t.op) {
    case OP_NOP:
        fprintf(of, "%s\n", op_str);
        break;
    case OP_GDECL:
    fprintf(of, "%s %s, %s\n", op_str, result_str, arg1_str);
        break;
    case OP_DECL:
        fprintf(of, "%s %s\n", op_str, result_str);
        break;
    case OP_ASSIGN:
        fprintf(of, "%s %s %s\n", result_str, op_str, arg1_str);
        break;
    case OP_ADD:
    case OP_SUB:
    case OP_MUL:
    case OP_DIV:
    case OP_REM:
        fprintf(of, "%s = %s %s %s\n", result_str, arg1_str, op_str, arg2_str);
        break;
    case OP_INC:
    case OP_DEC:
        fprintf(of, "%s%s\n", result_str, op_str);
        break;
    case OP_NEG:
        fprintf(of, "%s = %s%s\n", result_str, op_str, arg1_str);
        break;
    case OP_OR:
    case OP_AND:
        fprintf(of, "%s = %s %s %s\n", result_str, arg1_str, op_str, arg2_str);
        break;
    case OP_NOT:
        fprintf(of, "%s = %s %s\n", result_str, op_str, arg1_str);
        break;
    case OP_EQ:
    case OP_NEQ:
    case OP_GT:
    case OP_LT:
    case OP_GE:
    case OP_LE:
        fprintf(of, "%s = %s %s %s\n", result_str, arg1_str, op_str, arg2_str);
        break;
    case OP_JUMP:
        fprintf(of, "%s %s\n", op_str, result_str);
        break;
    case OP_JUMPIF:
    case OP_JUMPIFZ:
        fprintf(of, "%s %s, %s\n", op_str, result_str, arg1_str);
        break;
    case OP_LABEL:
        fprintf(of, "%s%s\n", result_str, op_str);
        break;
    case OP_PRINT:
    case OP_INPUT:
    case OP_ARG:
    case OP_CALL:
    case OP_GETRET:
    case OP_PARAM:
        fprintf(of, "%s %s\n", op_str, result_str);
        break;
    case OP_RET:
        fprintf(of, "%s\n", op_str);
        break;
    case OP_RETV:
        fprintf(of, "%s %s\n", op_str, result_str);
        break;
    case OP_ICAST:
    case OP_FCAST:
    case OP_DCAST:
        fprintf(of, "%s = %s(%s)\n", op_str, result_str, arg1_str);
    }
}

void tac_list_init() {
    tl = (tac_list *)malloc(sizeof(tac_list));
    tl->t = (tac *)malloc(TAC_LIST_INIT_CAP * sizeof(tac));
    tl->size = 0;
    tl->capacity = TAC_LIST_INIT_CAP;
}

void tac_list_add(tac t) {
    if (tl->size >= tl->capacity) {
        tl->capacity *= 2;
        tl->t = (tac *)realloc(tl->t, tl->capacity * sizeof(tac));
    }
    tl->t[tl->size++] = t;
}

void tac_list_free() {
    free(tl->t);
    free(tl);
}

void tac_list_print(FILE *of) {
    int i;
    for (i = 0; i < tl->size; i++) {
        tac_print(of, tl->t[i]);
    }
}

/* ---------------------HELPER FUNCTIONS-------------------- */

operand op_none() {
    operand operand;
    operand.kind = OPERAND_NONE;
    return operand;
}

operand op_const(ast_node *constant_node) {
    operand operand;
    operand.kind = OPERAND_CONST;
    operand.as.constant.constant_node = constant_node;
    return operand;
}
operand op_var(symtab_entry *entry) {
    operand operand;
    operand.kind = OPERAND_VAR;
    operand.as.variable.entry = entry;
    return operand;
}

operand op_temp(symtab_entry *entry) {
    operand operand;
    operand.kind = OPERAND_TEMP;
    operand.as.temporary.entry = entry;
    return operand;
}

operand op_label(const char *s) {
    operand operand;
    operand.kind = OPERAND_LABEL;
    operand.as.label.s = s;
    return operand;
}

operand op_string(const char *s) {
    operand operand;
    operand.kind = OPERAND_STRING;
    operand.as.string.s = s;
    return operand;
}

const char *op_code_to_string(op_code op) {
    switch (op) {
    case OP_NOP:
        return ";";
    /* Global Declaration */
    case OP_GDECL:
        return "global_declare";
    /* Declaration */
    case OP_DECL:
        return "declare";
    /* Assignment */
    case OP_ASSIGN:
        return "=";
    /* Arithmetic */
    case OP_ADD:
        return "+";
    case OP_SUB:
        return "-";
    case OP_MUL:
        return "*";
    case OP_DIV:
        return "/";
    case OP_REM:
        return "%%";
    /* Unary */
    case OP_INC:
        return "++";
    case OP_DEC:
        return "--";
    case OP_NEG:
        return "-";
    /* Logical */
    case OP_OR:
        return "or";
    case OP_AND:
        return "and";
    case OP_NOT:
        return "not";
    /* Comparison */
    case OP_EQ:
        return "==";
    case OP_NEQ:
        return "!=";
    case OP_GT:
        return ">";
    case OP_LT:
        return "<";
    case OP_GE:
        return ">=";
    case OP_LE:
        return "<=";
    /* Control Flow */
    case OP_JUMP:
        return "jump";
    case OP_JUMPIF:
        return "jumpif";
    case OP_JUMPIFZ:
        return "jumpifz";
    case OP_LABEL:
        return ":";
    /* I/O */
    case OP_PRINT:
        return "print";
    case OP_INPUT:
        return "input";
    /* Functions */
    case OP_ARG:
        return "arg";
    case OP_CALL:
        return "call";
    case OP_GETRET:
        return "getret";
    case OP_PARAM:
        return "param";
    case OP_RET:
        return "ret";
    case OP_RETV:
        return "retv";
    /* Type Casting */
    case OP_ICAST:
        return "icast";
    case OP_FCAST:
        return "fcast";
    case OP_DCAST:
        return "dcast";
    default:
        return "_error";
    }
}

const char *operand_to_string(operand arg) {
    char *operand_string;
    switch (arg.kind) {
    case OPERAND_NONE:
        return "_none";
    case OPERAND_CONST:
        operand_string = (char *)malloc(40 * sizeof(char));
        switch (arg.as.constant.constant_node->as.constant.d_type) {
        case UNDEF_TYPE:
            sprintf(operand_string, "_error");
            break;
        case INT_TYPE:
            sprintf(operand_string, "%d",
                    arg.as.constant.constant_node->as.constant.val.ival);
            break;
        case CHAR_TYPE:
            sprintf(operand_string, "%d",
                    arg.as.constant.constant_node->as.constant.val.cval);
            break;
        case FLOAT_TYPE:
            sprintf(operand_string, "%f",
                    arg.as.constant.constant_node->as.constant.val.fval);
            break;
        case DOUBLE_TYPE:
            sprintf(operand_string, "%lf",
                    arg.as.constant.constant_node->as.constant.val.fval);
            break;
        case VOID_TYPE:
            sprintf(operand_string, "_error");
        }
        return operand_string;
    case OPERAND_VAR:
        return arg.as.variable.entry->id;
    case OPERAND_TEMP:
        return arg.as.temporary.entry->id;
    case OPERAND_LABEL:
        return arg.as.label.s;
    case OPERAND_STRING:
        return arg.as.string.s;
    default:
        return "_error";
    }
}