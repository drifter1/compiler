#include "../include/semantics.h"

void semantic_analysis(ast_node *ast_node) {

    switch (ast_node->kind) {
    case PROGRAM:
        printf("Semantic analysis of Program Node\n");
        semantic_analysis_list(ast_node->as.program.declarations);
        semantic_analysis_list(ast_node->as.program.functions);
        semantic_analysis(ast_node->as.program.main_function);
        break;
    case DECLARATION:
        printf("Semantic analysis of Declaration Node\n");
        list_node *head = ast_node->as.declaration.names;
        while (head != NULL) {
            symtab_entry *entry = (symtab_entry *)head->data;
            entry->as.variable.d_type = ast_node->as.declaration.d_type;
            head = head->next;
        }
        break;
    case CONSTANT:
        printf("Semantic analysis of Constant Node\n");
        break;
    case FUNCTION:
        printf("Semantic analysis of Function Node\n");
        semantic_analysis(ast_node->as.function.function_tail);
        break;
    case FUNCTION_TAIL:
        printf("Semantic analysis of Function Tail Node\n");
        semantic_analysis_list(ast_node->as.function_tail.declarations);
        semantic_analysis_list(ast_node->as.function_tail.statements);
        break;
    case IF_STATEMENT:
        printf("Semantic analysis of If Statement Node\n");
        semantic_analysis(ast_node->as.if_statement.condition);
        semantic_analysis_list(ast_node->as.if_statement.if_branch);
        semantic_analysis_list(ast_node->as.if_statement.else_if_branches);
        semantic_analysis_list(ast_node->as.if_statement.else_branch);
        break;
    case EXPRESSION_BINARY:
        printf("Semantic analysis of Binary Expression Node\n");
        break;
    case EXPRESSION_UNARY:
        printf("Semantic analysis of Unary Expression Node\n");
        break;
    case VARIABLE_REFERENCE:
        printf("Semantic analysis of Variable Reference Node\n");
        break;
    case FUNCTION_CALL:
        printf("Semantic analysis of Function Call Node\n");
        break;
    case ELSE_IF:
        printf("Semantic analysis of Else If Node\n");
        semantic_analysis(ast_node->as.else_if.condition);
        semantic_analysis_list(ast_node->as.else_if.else_if_branch);
        break;
    case FOR_LOOP:
        printf("Semantic analysis of For Loop Node\n");
        semantic_analysis(ast_node->as.for_loop.initialize);
        semantic_analysis(ast_node->as.for_loop.condition);
        semantic_analysis(ast_node->as.for_loop.increment);
        semantic_analysis_list(ast_node->as.for_loop.for_branch);
        break;
    case ASSIGNMENT:
        printf("Semantic analysis of Assignment Node\n");
        break;
    case WHILE_LOOP:
        printf("Semantic analysis of While Loop Node\n");
        semantic_analysis(ast_node->as.while_loop.condition);
        semantic_analysis_list(ast_node->as.while_loop.while_branch);
        break;
    case JUMP_STATEMENT:
        printf("Semantic analysis of Jump Statement Node\n");
        break;
    case PRINT_STATEMENT:
        printf("Semantic analysis of Print Statement Node\n");
        break;
    case INPUT_STATEMENT:
        printf("Semantic analysis of Input Statement Node\n");
        break;
    case RETURN_STATEMENT:
        printf("Semantic analysis of Return Statement Node\n");
        break;
    }
}

void semantic_analysis_list(list_node *list_head) {
    list_node *head;
    ast_node *ast_node;
    head = list_head;
    while (head != NULL) {
        ast_node = (struct ast_node *)head->data;
        semantic_analysis(ast_node);
        head = head->next;
    }
}

data_type get_result_type(data_type type_1, data_type type_2,
                          operator_type op_type) {}

void type_error(data_type type_1, data_type type_2, operator_type op_type) {}

data_type expression_data_type(ast_node *ast_node) {}