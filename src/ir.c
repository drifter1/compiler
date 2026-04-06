#include "../include/ir.h"
#include <stdlib.h>

/* ----------------------MAIN FUNCTIONS--------------------- */

void intermediate_code_generation(ast_node *node) {

    if (node == NULL)
        return;

    switch (node->kind) {
    case PROGRAM:
        intermediate_code_generation_program(node);
        break;
    case DECLARATION:
        intermediate_code_generation_declaration(node);
        break;
    case CONSTANT:
        intermediate_code_generation_constant(node);
        break;
    case FUNCTION:
        intermediate_code_generation_function(node);
        break;
    case FUNCTION_TAIL:
        intermediate_code_generation_function_tail(node);
        break;
    case IF_STATEMENT:
        intermediate_code_generation_if_statement(node);
        break;
    case EXPRESSION_BINARY:
        intermediate_code_generation_expresssion_binary(node);
        break;
    case EXPRESSION_UNARY:
        intermediate_code_generation_expresssion_unary(node);
        break;
    case VARIABLE_REFERENCE:
        intermediate_code_generation_variable_reference(node);
        break;
    case FUNCTION_CALL:
        intermediate_code_generation_function_call(node);
        break;
    case ELSE_IF:
        intermediate_code_generation_else_if(node);
        break;
    case FOR_LOOP:
        intermediate_code_generation_for_loop(node);
        break;
    case ASSIGNMENT:
        intermediate_code_generation_assignment(node);
        break;
    case WHILE_LOOP:
        intermediate_code_generation_while_loop(node);
        break;
    case JUMP_STATEMENT:
        intermediate_code_generation_jump_statement(node);
        break;
    case PRINT_STATEMENT:
        intermediate_code_generation_print_statement(node);
        break;
    case INPUT_STATEMENT:
        intermediate_code_generation_input_statement(node);
        break;
    case RETURN_STATEMENT:
        intermediate_code_generation_return_statement(node);
    }
}

void intermediate_code_generation_list(list_node *list_head) {
    list_node *head;
    ast_node *node;
    head = list_head;
    while (head != NULL) {
        node = (ast_node *)head->data;
        intermediate_code_generation(node);
        head = head->next;
    }
}

void intermediate_code_generation_program(ast_node *node) {
    intermediate_code_generation_list(node->as.program.declarations);
    intermediate_code_generation(node->as.program.main_function);
    intermediate_code_generation_list(node->as.program.functions);
}

void intermediate_code_generation_declaration(ast_node *node) {}

void intermediate_code_generation_constant(ast_node *node) {}

void intermediate_code_generation_function(ast_node *node) {
    intermediate_code_generation(node->as.function.function_tail);
}

void intermediate_code_generation_function_tail(ast_node *node) {
    intermediate_code_generation_list(node->as.function_tail.declarations);
    intermediate_code_generation_list(node->as.function_tail.statements);
}

void intermediate_code_generation_if_statement(ast_node *node) {
    intermediate_code_generation(node->as.if_statement.condition);
    intermediate_code_generation_list(node->as.if_statement.if_branch);
    intermediate_code_generation_list(node->as.if_statement.else_if_branches);
    intermediate_code_generation_list(node->as.if_statement.else_branch);
}

void intermediate_code_generation_expresssion_binary(ast_node *node) {
    intermediate_code_generation(node->as.expression_binary.left);
    intermediate_code_generation(node->as.expression_binary.right);
}

void intermediate_code_generation_expresssion_unary(ast_node *node) {
    intermediate_code_generation(node->as.expression_unary.operand);
}

void intermediate_code_generation_variable_reference(ast_node *node) {}

void intermediate_code_generation_function_call(ast_node *node) {
    intermediate_code_generation_list(node->as.function_call.arguments);
}

void intermediate_code_generation_else_if(ast_node *node) {
    intermediate_code_generation(node->as.else_if.condition);
    intermediate_code_generation_list(node->as.else_if.else_if_branch);
}

void intermediate_code_generation_for_loop(ast_node *node) {
    intermediate_code_generation(node->as.for_loop.initialize);
    intermediate_code_generation(node->as.for_loop.condition);
    intermediate_code_generation_list(node->as.for_loop.for_branch);
    intermediate_code_generation(node->as.for_loop.increment);
}

void intermediate_code_generation_assignment(ast_node *node) {
    intermediate_code_generation(node->as.assignment.expression);
    intermediate_code_generation(node->as.assignment.variable_reference);
}

void intermediate_code_generation_while_loop(ast_node *node) {
    intermediate_code_generation(node->as.while_loop.condition);
    intermediate_code_generation_list(node->as.while_loop.while_branch);
}

void intermediate_code_generation_jump_statement(ast_node *node) {}

void intermediate_code_generation_print_statement(ast_node *node) {
    print_type p_type = node->as.print_statement.p_type;
    switch (p_type) {
    case EXPRESSION:
        intermediate_code_generation(
            node->as.print_statement.print_value.expression);
        break;
    case STRING:
        break;
    }
}

void intermediate_code_generation_input_statement(ast_node *node) {
    intermediate_code_generation(node->as.input_statement.variable_reference);
}

void intermediate_code_generation_return_statement(ast_node *node) {
    ast_node *expression = node->as.return_statement.expression;
    if (expression != NULL) {
        intermediate_code_generation(expression);
    }
}