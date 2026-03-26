#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

/* --------------------DATA TYPES-------------------- */

typedef enum {
    UNDEF_TYPE,
    INT_TYPE,
    CHAR_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
    VOID_TYPE
} data_type;

/* ----------------------VALUES---------------------- */

typedef union {
    int ival;
    double fval;
    char cval;
    char *sval;
} value;

/* ------------------OPERATOR TYPES------------------ */

typedef enum {
    NO_OP,         // no operation
    ASSIGN,        // a = b
    INC,           // ++a or a++
    DEC,           // --a or a--
    PRE_INC,       // ++a
    PRE_DEC,       // --a
    POST_INC,      // a++
    POST_DEC,      // a--
    ADD,           // a + b
    SUB,           // a - b
    MUL,           // a * b
    DIV,           // a / b
    REM,           // a % b
    UNARY_PLUS,    // +a
    UNARY_MINUS,   // -a
    OR,            // a || b
    AND,           // a && b
    NOT,           // !a
    EQUAL,         // a == b
    NOT_EQUAL,     // a != b
    GREATER,       // a > b
    LESS,          // a < b
    GREATER_EQUAL, // a >= b
    LESS_EQUAL     // a <= b
} operator_type;

/* -------------------FIXITY TYPES------------------- */

typedef enum { PREFIX, POSTFIX } fixity_type;

/* --------------------JUMP TYPES-------------------- */

typedef enum { CONTINUE, BREAK } jump_type;

/* -------------------PRINT TYPES-------------------- */

typedef enum { EXPRESSION, STRING } print_type;

/* ------------------TYPE PROMOTION------------------ */

extern const data_type implicit_type_promotion_matrix[6][6];
data_type promote_data_type(data_type origin_type, data_type target_type);

/* ------------------OPERATOR RESULT----------------- */

typedef struct op_result {
    data_type d_type;
    bool needs_truthy;
    bool produce_bool;
} op_result;

op_result get_op_result_type(operator_type op_type, data_type left_type,
                             data_type right_type);

/* -----------------DISPLAY FUNCTIONS---------------- */

char *data_type_to_string(data_type d_type);
char *operator_type_to_string(operator_type op_type);
char *jump_type_to_string(jump_type j_type);
char *print_type_to_string(print_type p_type);

#endif /* TYPES_H */