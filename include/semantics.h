/* token types */
#define UNDEF 0
#define INT_TYPE 1
#define REAL_TYPE 2
#define CHAR_TYPE 3
#define STR_TYPE 4
#define ARRAY_TYPE 5
#define POINTER_TYPE 6
#define FUNCTION_TYPE 7
#define VOID_TYPE 8

/* operator types */
#define NONE 0		// to check types only - assignment, parameter
#define ARITHM_OP 1 // ADDOP, MULOP, DIVOP (+, -, *, /)
#define INCR_OP 2   // INCR (++, --)
#define BOOL_OP 3   // OROP, ANDOP (||, &&)
#define NOT_OP 4    // NOTOP (!)
#define REL_OP 5    // RELOP (>, <, >=, <=)
#define EQU_OP 6    // EQUOP (==, !=)

// Function Declarations
int get_result_type (int type_1, int type_2, int op_type); /* type check and result type */
void type_error(int type_1, int type_2, int op_type);      /* print type error */
