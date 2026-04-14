#ifndef ERROR_H
#define ERROR_H

/* -----------------------ERROR KINDS----------------------- */

typedef enum { ERROR, WARNING, NOTE } error_kind;

/* -----------------LEXICAL ANALYSIS ERRORS----------------- */

/* End-of-file encountered in comment */
#define EOF_IN_COMMENT "EOF in comment"
/* Unrecognized character in source */
#define UNRECOGNIZED_CHARACTER "unrecognized character \'%c\' (ASCII value: %d)"

/* -----------------SYNTAX ANALYSIS ERRORS------------------ */

/* Missing semicolon */
#define MISSING_SEMICOLON "expected \';\' at the end of the statement"

/* -----------------SEMANTIC ANALYSIS ERRORS---------------- */

/* Binary expression operands mismatch. */
#define ERR_BIN_INVALID_OPERANDS                                               \
    "invalid operands to binary expression (%s and %s) with operator \'%s\'"
/* Unary expression operands mismatch. */
#define ERR_UNARY_INVALID_OPERANDS                                             \
    "invalid operand to unary expression (%s) with operator \'%s\'"
/* Assignment type incompatibility. */
#define ERR_ASSIGN_INCOMPATIBLE                                                \
    "cannot assign value of type %s to variable of type %s"
/* jump statement outside of loop. */
#define ERR_JUMP_NOT_IN_LOOP "\'%s\' not within a loop"
/* output statement type. */
#define ERR_OUTPUT_TYPE "output value of \'output\' statement has type %s"
/* Redeclaration of an identifier as a variable. */
#define ERR_REDECLARED_VAR "identifier \'%s\' redeclared as variable"
/* Incompatible initialization of a variable. */
#define ERR_VAR_INIT_INCOMPATIBLE                                              \
    "variable \'%s\' of type %s initialized with incompatible type %s"
/* Redeclaration of an identifier as a function. */
#define ERR_REDECLARED_FUNC "identifier \'%s\' redeclared as function"
/* Missing required return statement. */
#define ERR_MISSING_RETURN                                                     \
    "missing return statement in function \'%s\' returning %s"
/* More than one return statements in a function. */
#define ERR_MULTIPLE_RETURNS "multiple return statements in function \'%s\'"
/* Use of an undeclared variable. */
#define ERR_UNDECLARED_VAR "use of undeclared variable \'%s\'"
/* Wrong number of arguments in function call. */
#define ERR_FUNC_ARG_NUM_MISMATCH                                              \
    "function called with %d arguments; expected %d"
/* Type‑incompatible argument in function call. */
#define ERR_FUNC_ARG_TYPE_MISMATCH                                             \
    "argument of type %s for parameter \'%s\' (expected %s) is incompatible"
/* Return statement returning a value when the function is void. */
#define ERR_RETURN_VALUE_IN_VOID                                               \
    "return statement returns a value in a void function"
/* Return statement that should return a value but returns none. */
#define ERR_RETURN_NO_VALUE                                                    \
    "return statement does not return a value in function returning %s"
/* Return value not compatible with the function’s return type. */
#define ERR_RETURN_TYPE_MISMATCH                                               \
    "return value type %s not compatible with function return type %s"

/* ----------------ERROR REPORTING FUNCTIONS---------------- */

void internal_error(const char *error);
void lexical_analysis_error(const char *error, ...);
void syntax_analysis_error(int lineno, const char *error, ...);
void semantic_analysis_error(int lineno, const char *error, ...);

/* ---------------------HELPER FUNCTIONS-------------------- */

int find_token_start_col(const char *line, const char *token);
void print_colored_line(const char *line, const char *token, int len);

#endif /* ERROR_H */