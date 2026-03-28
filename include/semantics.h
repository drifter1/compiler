#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "ast.h"

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

void set_declaration_names_type(data_type d_type, list_node *names);
void verify_declaration_names_init_value(list_node *names);
void verify_variable_declaration_before_use(symtab_entry *entry,
                                            int use_lineno);
void set_return_statement_ret_type(ast_node *node);
data_type expression_data_type(ast_node *node);

#endif /* SEMANTICS_H */