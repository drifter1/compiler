#ifndef TAC_H
#define TAC_H

#include "ast.h"

/* ----------------------Operator Codes--------------------- */

typedef enum {
    OP_NOP,
    /* Declaration */
    OP_DECL,
    /* Assignment */
    OP_ASSIGN,
    /* Arithmetic */
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_REM,
    /* Unary */
    OP_INC,
    OP_DEC,
    OP_NEG,
    /* Logical */
    OP_OR,
    OP_AND,
    OP_NOT,
    /* Comparison */
    OP_EQ,
    OP_NEQ,
    OP_GT,
    OP_LT,
    OP_GE,
    OP_LE,
    /* Control Flow */
    OP_JUMP,
    OP_JUMPIF,
    OP_JUMPIFZ,
    OP_LABEL,
    /* I/O */
    OP_PRINT,
    OP_INPUT,
    /* Functions */
    OP_ARG,
    OP_CALL,
    OP_GETRET,
    OP_PARAM,
    OP_RET,
    OP_RETV,
    /* Type Casting */
    OP_ICAST,
    OP_FCAST,
    OP_DCAST
} op_code;

/* -----------------------Operand Kinds--------------------- */

typedef enum {
    OPERAND_NONE,
    OPERAND_CONST,
    OPERAND_VAR,
    OPERAND_TEMP,
    OPERAND_LABEL,
    OPERAND_STRING
} operand_kind;

/* -------------------------Operand------------------------- */

typedef struct operand {
    operand_kind kind;
    union {
        struct {
            ast_node *constant_node;
        } constant;
        struct {
            symtab_entry *entry;
        } variable;
        struct {
            symtab_entry *entry;
        } temporary;
        struct {
            const char *s;
        } label;
        struct {
            const char *s;
        } string;
    } as;
} operand;

/* -----------------Three Address Code (TAC)---------------- */

typedef struct tac {
    op_code op;
    operand result;
    operand arg1;
    operand arg2;
} tac;

/* -------------------------TAC List------------------------ */

typedef struct {
    tac *t;
    int size;
    int capacity;
} tac_list;

/* ------------------TAC LIST CONFIGURATION----------------- */

#define TAC_LIST_INIT_CAP 8

/* --------------------TAC LIST STRUCTURE------------------- */

extern tac_list *tl;

/* ----------------------MAIN FUNCTIONS--------------------- */

tac tac_create(op_code op, operand result, operand arg1, operand arg2);
void tac_print(FILE *of, tac t);

void tac_list_init();
void tac_list_add(tac t);
void tac_list_free();
void tac_list_print(FILE *of);

/* ---------------------HELPER FUNCTIONS-------------------- */

operand op_none();
operand op_const(ast_node *constant_node);
operand op_var(symtab_entry *entry);
operand op_temp(symtab_entry *entry);
operand op_label(const char *s);
operand op_string(const char *s);

const char *op_code_to_string(op_code op);
const char *operand_to_string(operand arg);

#endif /* TAC_H */