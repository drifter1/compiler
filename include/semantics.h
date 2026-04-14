#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "ast.h"

/* -----------------DATA TYPE COMPATIBILITY----------------- */

typedef enum { NOT_COMPATIBLE, SAME_TYPE, COMPATIBLE } dtype_compatibility;

/* ------------------RETURN STATEMENT COUNT----------------- */

extern int return_count;

/* ------------------------LOOP DEPTH----------------------- */

extern int loop_depth;

/* ----------------------MAIN FUNCTIONS--------------------- */

void semantic_analysis(ast_node *node);
void semantic_analysis_list(list_node *list_head);
void semantic_analysis_program(ast_node *node);
void semantic_analysis_declaration(ast_node *node);
void semantic_analysis_constant(ast_node *node);
void semantic_analysis_function(ast_node *node);
void semantic_analysis_function_tail(ast_node *node);
void semantic_analysis_if_statement(ast_node *node);
void semantic_analysis_expresssion_binary(ast_node *node);
void semantic_analysis_expresssion_unary(ast_node *node);
void semantic_analysis_variable_reference(ast_node *node);
void semantic_analysis_function_call(ast_node *node);
void semantic_analysis_else_if(ast_node *node);
void semantic_analysis_for_loop(ast_node *node);
void semantic_analysis_assignment(ast_node *node);
void semantic_analysis_while_loop(ast_node *node);
void semantic_analysis_jump_statement(ast_node *node);
void semantic_analysis_print_statement(ast_node *node);
void semantic_analysis_input_statement(ast_node *node);
void semantic_analysis_return_statement(ast_node *node);

/* ---------------------HELPER FUNCTIONS-------------------- */

void verify_no_redeclaration_of_names(list_node *names, int declaration_lineno);
void set_declaration_names_type(data_type d_type, list_node *names);
dtype_compatibility verify_assignment_dtype_compatible(data_type lhs_dtype,
                                                       data_type rhs_dtype,
                                                       int rhs_is_constant);
void verify_declaration_names_init_value(list_node *names);
void verify_no_redeclaration_of_function_name(symtab_entry *entry,
                                              int declaration_lineno);
void verify_return_statement_last(list_node *statements);
void verify_variable_declaration_before_use(symtab_entry *entry,
                                            int use_lineno);
void verify_function_call_argument_count(list_node *parameters,
                                         list_node *arguments, int lineno);
void verify_function_call_argument_types(list_node *parameters,
                                         list_node *arguments, int lineno);
void set_return_statement_ret_type(ast_node *node);
void verify_return_statement_ret_type(ast_node *node);
data_type expression_data_type(ast_node *node);

#endif /* SEMANTICS_H */