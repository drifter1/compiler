#ifndef IR_H
#define IR_H

#include "tac.h"

/* ----------------------MAIN FUNCTIONS--------------------- */

void intermediate_code_generation(ast_node *node);
void intermediate_code_generation_list(list_node *list_head);
void intermediate_code_generation_program(ast_node *node);
void intermediate_code_generation_declaration(ast_node *node);
operand intermediate_code_generation_constant(ast_node *node);
void intermediate_code_generation_function(ast_node *node);
void intermediate_code_generation_function_tail(ast_node *node);
void intermediate_code_generation_if_statement(ast_node *node);
operand intermediate_code_generation_expression_binary(ast_node *node);
operand intermediate_code_generation_expression_unary(ast_node *node);
operand intermediate_code_generation_variable_reference(ast_node *node);
operand intermediate_code_generation_function_call(ast_node *node);
void intermediate_code_generation_else_if(ast_node *node);
void intermediate_code_generation_for_loop(ast_node *node);
void intermediate_code_generation_assignment(ast_node *node);
void intermediate_code_generation_while_loop(ast_node *node);
void intermediate_code_generation_jump_statement(ast_node *node);
void intermediate_code_generation_print_statement(ast_node *node);
void intermediate_code_generation_input_statement(ast_node *node);
void intermediate_code_generation_return_statement(ast_node *node);

/* ---------------------HELPER FUNCTIONS-------------------- */

operand intermediate_code_generation_expression(ast_node *node);
op_code operator_type_to_op_code(operator_type op_type);
symtab_entry *new_temporary(int lineno, data_type d_type);
char *new_label();

#endif /* IR_H */