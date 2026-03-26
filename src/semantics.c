#include "../include/semantics.h"

/* ----------------------MAIN FUNCTIONS--------------------- */

void semantic_analysis(ast_node *ast_node) {

    switch (ast_node->kind) {
    case PROGRAM:
        semantic_analysis_program(ast_node);
        break;
    case DECLARATION:
        semantic_analysis_declaration(ast_node);
        break;
    case CONSTANT:
        semantic_analysis_constant(ast_node);
        break;
    case FUNCTION:
        semantic_analysis_function(ast_node);
        break;
    case FUNCTION_TAIL:
        semantic_analysis_function_tail(ast_node);
        break;
    case IF_STATEMENT:
        semantic_analysis_if_statement(ast_node);
        break;
    case EXPRESSION_BINARY:
        semantic_analysis_expresssion_binary(ast_node);
        break;
    case EXPRESSION_UNARY:
        semantic_analysis_expresssion_unary(ast_node);
        break;
    case VARIABLE_REFERENCE:
        semantic_analysis_variable_reference(ast_node);
        break;
    case FUNCTION_CALL:
        semantic_analysis_function_call(ast_node);
        break;
    case ELSE_IF:
        semantic_analysis_else_if(ast_node);
        break;
    case FOR_LOOP:
        semantic_analysis_for_loop(ast_node);
        break;
    case ASSIGNMENT:
        semantic_analysis_assignment(ast_node);
        break;
    case WHILE_LOOP:
        semantic_analysis_while_loop(ast_node);
        break;
    case JUMP_STATEMENT:
        semantic_analysis_jump_statement(ast_node);
        break;
    case PRINT_STATEMENT:
        semantic_analysis_print_statement(ast_node);
        break;
    case INPUT_STATEMENT:
        semantic_analysis_input_statement(ast_node);
        break;
    case RETURN_STATEMENT:
        semantic_analysis_return_statement(ast_node);
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

void semantic_analysis_program(ast_node *ast_node) {
    printf("Semantic analysis of Program Node\n");
    semantic_analysis_list(ast_node->as.program.declarations);
    semantic_analysis_list(ast_node->as.program.functions);
    semantic_analysis(ast_node->as.program.main_function);
}

void semantic_analysis_declaration(ast_node *ast_node) {
    printf("Semantic analysis of Declaration Node\n");
    set_declaration_names_type(ast_node->as.declaration.d_type,
                               ast_node->as.declaration.names);
}

void semantic_analysis_constant(ast_node *ast_node) {
    printf("Semantic analysis of Constant Node\n");
    printf("Constant Node of data type \'%s\'\n",
           data_type_to_string(ast_node->as.constant.d_type));
}

void semantic_analysis_function(ast_node *ast_node) {
    printf("Semantic analysis of Function Node\n");
    semantic_analysis(ast_node->as.function.function_tail);
}

void semantic_analysis_function_tail(ast_node *ast_node) {
    printf("Semantic analysis of Function Tail Node\n");
    semantic_analysis_list(ast_node->as.function_tail.declarations);
    semantic_analysis_list(ast_node->as.function_tail.statements);
}

void semantic_analysis_if_statement(ast_node *ast_node) {
    printf("Semantic analysis of If Statement Node\n");
    semantic_analysis(ast_node->as.if_statement.condition);
    semantic_analysis_list(ast_node->as.if_statement.if_branch);
    semantic_analysis_list(ast_node->as.if_statement.else_if_branches);
    semantic_analysis_list(ast_node->as.if_statement.else_branch);
}

void semantic_analysis_expresssion_binary(ast_node *ast_node) {
    printf("Semantic analysis of Binary Expression Node\n");

    semantic_analysis(ast_node->as.expression_binary.left);
    semantic_analysis(ast_node->as.expression_binary.right);

    data_type d_type = expression_data_type(ast_node);

    printf("Result data type is \'%s\'\n", data_type_to_string(d_type));
}

void semantic_analysis_expresssion_unary(ast_node *ast_node) {
    printf("Semantic analysis of Unary Expression Node\n");

    semantic_analysis(ast_node->as.expression_unary.operand);

    data_type d_type = expression_data_type(ast_node);

    printf("Result data type is \'%s\'\n", data_type_to_string(d_type));
}

void semantic_analysis_variable_reference(ast_node *ast_node) {
    printf("Semantic analysis of Variable Reference Node\n");

    symtab_entry *entry = ast_node->as.variable_reference.entry;

    printf("Reference of variable \'%s\' in scope \'%s\'\n", entry->id,
           entry->scope->id);
}

void semantic_analysis_function_call(ast_node *ast_node) {
    printf("Semantic analysis of Function Call Node\n");

    semantic_analysis_list(ast_node->as.function_call.arguments);
}

void semantic_analysis_else_if(ast_node *ast_node) {
    printf("Semantic analysis of Else If Node\n");
    semantic_analysis(ast_node->as.else_if.condition);
    semantic_analysis_list(ast_node->as.else_if.else_if_branch);
}

void semantic_analysis_for_loop(ast_node *ast_node) {
    printf("Semantic analysis of For Loop Node\n");
    semantic_analysis(ast_node->as.for_loop.initialize);
    semantic_analysis(ast_node->as.for_loop.condition);
    semantic_analysis(ast_node->as.for_loop.increment);
    semantic_analysis_list(ast_node->as.for_loop.for_branch);
}

void semantic_analysis_assignment(ast_node *ast_node) {
    printf("Semantic analysis of Assignment Node\n");

    semantic_analysis(ast_node->as.assignment.variable_reference);
    semantic_analysis(ast_node->as.assignment.expression);

    data_type lhs_dtype =
        get_data_type(ast_node->as.assignment.variable_reference->as
                          .variable_reference.entry->id);
    data_type rhs_dtype =
        expression_data_type(ast_node->as.assignment.expression);

    printf("LHS data type is \'%s\'\n", data_type_to_string(lhs_dtype));
    printf("RHS data type is \'%s\'\n", data_type_to_string(rhs_dtype));

    if (promote_data_type(lhs_dtype, rhs_dtype) == UNDEF_TYPE) {
        printf("Incompatible Types!\n");
    } else {
        printf("Compatible Types!\n");
    }
}

void semantic_analysis_while_loop(ast_node *ast_node) {
    printf("Semantic analysis of While Loop Node\n");
    semantic_analysis(ast_node->as.while_loop.condition);
    semantic_analysis_list(ast_node->as.while_loop.while_branch);
}

void semantic_analysis_jump_statement(ast_node *ast_node) {
    printf("Semantic analysis of Jump Statement Node\n");
    printf("Jump Statement Node of type \'%s\'\n",
           jump_type_to_string(ast_node->as.jump_statement.j_type));
}

void semantic_analysis_print_statement(ast_node *ast_node) {
    printf("Semantic analysis of Print Statement Node\n");

    data_type d_type;

    switch (ast_node->as.print_statement.p_type) {
    case EXPRESSION:
        d_type = expression_data_type(
            ast_node->as.print_statement.print_value.expression);
        printf("The data type of the output value is: \'%s\'\n",
               data_type_to_string(d_type));
        break;
    case STRING:
        printf("The output value is a STRING\n");
    }
}

void semantic_analysis_input_statement(ast_node *ast_node) {
    printf("Semantic analysis of Input Statement Node\n");
    data_type d_type =
        get_data_type(ast_node->as.input_statement.variable_reference->as
                          .variable_reference.entry->id);
    printf("The data type of the input is: \'%s\',",
           data_type_to_string(d_type));
}

void semantic_analysis_return_statement(ast_node *ast_node) {
    printf("Semantic analysis of Return Statement Node\n");
    set_return_statement_ret_type(ast_node);
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

void set_return_statement_ret_type(ast_node *ast_node) {
    ast_node->as.return_statement.ret_type =
        expression_data_type(ast_node->as.return_statement.expression);
}

data_type expression_data_type(ast_node *ast_node) {
    operator_type op_type;
    data_type left_type;
    data_type right_type;
    op_result result;

    switch (ast_node->kind) {
    case EXPRESSION_BINARY:
        op_type = ast_node->as.expression_binary.op_type;
        left_type = expression_data_type(ast_node->as.expression_binary.left);
        right_type = expression_data_type(ast_node->as.expression_binary.right);
        result = get_op_result_type(op_type, left_type, right_type);
        return result.d_type;
    case EXPRESSION_UNARY:
        op_type = ast_node->as.expression_unary.op_type;
        left_type = expression_data_type(ast_node->as.expression_unary.operand);
        right_type = UNDEF_TYPE;
        result = get_op_result_type(op_type, left_type, right_type);
        return result.d_type;
    case VARIABLE_REFERENCE:
        return get_data_type(ast_node->as.variable_reference.entry->id);
    case CONSTANT:
        return ast_node->as.constant.d_type;
    case FUNCTION_CALL:
        return get_data_type(ast_node->as.function_call.entry->id);
    default:
        return UNDEF_TYPE;
    }
}