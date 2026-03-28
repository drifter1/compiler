#include "../include/semantics.h"

/* ----------------------MAIN FUNCTIONS--------------------- */

void semantic_analysis(ast_node *node) {

    if (node == NULL)
        return;

    switch (node->kind) {
    case PROGRAM:
        semantic_analysis_program(node);
        break;
    case DECLARATION:
        semantic_analysis_declaration(node);
        break;
    case CONSTANT:
        semantic_analysis_constant(node);
        break;
    case FUNCTION:
        semantic_analysis_function(node);
        break;
    case FUNCTION_TAIL:
        semantic_analysis_function_tail(node);
        break;
    case IF_STATEMENT:
        semantic_analysis_if_statement(node);
        break;
    case EXPRESSION_BINARY:
        semantic_analysis_expresssion_binary(node);
        break;
    case EXPRESSION_UNARY:
        semantic_analysis_expresssion_unary(node);
        break;
    case VARIABLE_REFERENCE:
        semantic_analysis_variable_reference(node);
        break;
    case FUNCTION_CALL:
        semantic_analysis_function_call(node);
        break;
    case ELSE_IF:
        semantic_analysis_else_if(node);
        break;
    case FOR_LOOP:
        semantic_analysis_for_loop(node);
        break;
    case ASSIGNMENT:
        semantic_analysis_assignment(node);
        break;
    case WHILE_LOOP:
        semantic_analysis_while_loop(node);
        break;
    case JUMP_STATEMENT:
        semantic_analysis_jump_statement(node);
        break;
    case PRINT_STATEMENT:
        semantic_analysis_print_statement(node);
        break;
    case INPUT_STATEMENT:
        semantic_analysis_input_statement(node);
        break;
    case RETURN_STATEMENT:
        semantic_analysis_return_statement(node);
        break;
    }
}

void semantic_analysis_list(list_node *list_head) {
    list_node *head;
    ast_node *node;
    head = list_head;
    while (head != NULL) {
        node = (struct ast_node *)head->data;
        semantic_analysis(node);
        head = head->next;
    }
}

void semantic_analysis_program(ast_node *node) {
    printf("Semantic analysis of Program Node\n");
    semantic_analysis_list(node->as.program.declarations);
    semantic_analysis_list(node->as.program.functions);
    semantic_analysis(node->as.program.main_function);
}

void semantic_analysis_declaration(ast_node *node) {
    printf("Semantic analysis of Declaration Node\n");
    set_declaration_names_type(node->as.declaration.d_type,
                               node->as.declaration.names);
}

void semantic_analysis_constant(ast_node *node) {
    printf("Semantic analysis of Constant Node\n");
    printf("Constant Node of data type \'%s\'\n",
           data_type_to_string(node->as.constant.d_type));
}

void semantic_analysis_function(ast_node *node) {
    printf("Semantic analysis of Function Node\n");
    symtab_entry *entry = node->as.function.entry;
    enter_local_scope(entry->id);
    semantic_analysis(node->as.function.function_tail);
    hide_current_scope();
}

void semantic_analysis_function_tail(ast_node *node) {
    printf("Semantic analysis of Function Tail Node\n");
    semantic_analysis_list(node->as.function_tail.declarations);
    semantic_analysis_list(node->as.function_tail.statements);
}

void semantic_analysis_if_statement(ast_node *node) {
    printf("Semantic analysis of If Statement Node\n");
    semantic_analysis(node->as.if_statement.condition);
    semantic_analysis_list(node->as.if_statement.if_branch);
    semantic_analysis_list(node->as.if_statement.else_if_branches);
    semantic_analysis_list(node->as.if_statement.else_branch);
}

void semantic_analysis_expresssion_binary(ast_node *node) {
    printf("Semantic analysis of Binary Expression Node\n");

    semantic_analysis(node->as.expression_binary.left);
    semantic_analysis(node->as.expression_binary.right);

    data_type d_type = expression_data_type(node);

    printf("Result data type is \'%s\'\n", data_type_to_string(d_type));
}

void semantic_analysis_expresssion_unary(ast_node *node) {
    printf("Semantic analysis of Unary Expression Node\n");

    semantic_analysis(node->as.expression_unary.operand);

    data_type d_type = expression_data_type(node);

    printf("Result data type is \'%s\'\n", data_type_to_string(d_type));
}

void semantic_analysis_variable_reference(ast_node *node) {
    printf("Semantic analysis of Variable Reference Node\n");

    symtab_entry *entry = node->as.variable_reference.entry;

    printf("Reference of variable \'%s\' in scope \'%s\'\n", entry->id,
           entry->scope->id);
}

void semantic_analysis_function_call(ast_node *node) {
    printf("Semantic analysis of Function Call Node\n");

    semantic_analysis_list(node->as.function_call.arguments);
}

void semantic_analysis_else_if(ast_node *node) {
    printf("Semantic analysis of Else If Node\n");
    semantic_analysis(node->as.else_if.condition);
    semantic_analysis_list(node->as.else_if.else_if_branch);
}

void semantic_analysis_for_loop(ast_node *node) {
    printf("Semantic analysis of For Loop Node\n");
    semantic_analysis(node->as.for_loop.initialize);
    semantic_analysis(node->as.for_loop.condition);
    semantic_analysis(node->as.for_loop.increment);
    semantic_analysis_list(node->as.for_loop.for_branch);
}

void semantic_analysis_assignment(ast_node *node) {
    printf("Semantic analysis of Assignment Node\n");

    semantic_analysis(node->as.assignment.variable_reference);
    semantic_analysis(node->as.assignment.expression);

    data_type lhs_dtype = get_data_type(node->as.assignment.variable_reference
                                            ->as.variable_reference.entry->id);
    data_type rhs_dtype = expression_data_type(node->as.assignment.expression);

    printf("LHS data type is \'%s\'\n", data_type_to_string(lhs_dtype));
    printf("RHS data type is \'%s\'\n", data_type_to_string(rhs_dtype));

    if (promote_data_type(lhs_dtype, rhs_dtype) == UNDEF_TYPE) {
        printf("Incompatible Types!\n");
    } else {
        printf("Compatible Types!\n");
    }
}

void semantic_analysis_while_loop(ast_node *node) {
    printf("Semantic analysis of While Loop Node\n");
    semantic_analysis(node->as.while_loop.condition);
    semantic_analysis_list(node->as.while_loop.while_branch);
}

void semantic_analysis_jump_statement(ast_node *node) {
    printf("Semantic analysis of Jump Statement Node\n");
    printf("Jump Statement Node of type \'%s\'\n",
           jump_type_to_string(node->as.jump_statement.j_type));
}

void semantic_analysis_print_statement(ast_node *node) {
    printf("Semantic analysis of Print Statement Node\n");

    data_type d_type;

    switch (node->as.print_statement.p_type) {
    case EXPRESSION:
        semantic_analysis(node->as.print_statement.print_value.expression);
        d_type = expression_data_type(
            node->as.print_statement.print_value.expression);
        printf("The data type of the output value is: \'%s\'\n",
               data_type_to_string(d_type));
        break;
    case STRING:
        printf("The output value is a STRING\n");
    }
}

void semantic_analysis_input_statement(ast_node *node) {
    printf("Semantic analysis of Input Statement Node\n");
    semantic_analysis(node->as.input_statement.variable_reference);
    data_type d_type =
        get_data_type(node->as.input_statement.variable_reference->as
                          .variable_reference.entry->id);
    printf("The data type of the input is: \'%s\',",
           data_type_to_string(d_type));
}

void semantic_analysis_return_statement(ast_node *node) {
    printf("Semantic analysis of Return Statement Node\n");
    set_return_statement_ret_type(node);
    semantic_analysis(node->as.return_statement.expression);
}

/* ---------------------HELPER FUNCTIONS-------------------- */

void set_declaration_names_type(data_type d_type, list_node *names) {
    list_node *head = names;
    while (head != NULL) {
        symtab_entry *entry = (symtab_entry *)head->data;
        entry->as.variable.d_type = d_type;
        head = head->next;
    }
}

void set_return_statement_ret_type(ast_node *node) {
    ast_node *expression = node->as.return_statement.expression;
    if (expression != NULL) {
        node->as.return_statement.ret_type = expression_data_type(expression);
    }
    /* Else not required. Type is void in that case. */
}

data_type expression_data_type(ast_node *node) {
    operator_type op_type;
    data_type left_type;
    data_type right_type;

    switch (node->kind) {
    case EXPRESSION_BINARY:
        op_type = node->as.expression_binary.op_type;
        left_type = expression_data_type(node->as.expression_binary.left);
        right_type = expression_data_type(node->as.expression_binary.right);
        return get_op_result_type(op_type, left_type, right_type);
    case EXPRESSION_UNARY:
        op_type = node->as.expression_unary.op_type;
        left_type = expression_data_type(node->as.expression_unary.operand);
        right_type = UNDEF_TYPE;
        return get_op_result_type(op_type, left_type, right_type);
    case VARIABLE_REFERENCE:
        return get_data_type(node->as.variable_reference.entry->id);
    case CONSTANT:
        return node->as.constant.d_type;
    case FUNCTION_CALL:
        return get_data_type(node->as.function_call.entry->id);
    default:
        return UNDEF_TYPE;
    }
}