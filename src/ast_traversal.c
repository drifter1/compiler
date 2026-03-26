#include "../include/ast.h"

/* ---------------------AST TRAVERSAL----------------------- */

void ast_print_node(ast_node *node) {
    list_node *head;
    symtab_entry *entry;

    switch (node->kind) {
    case PROGRAM:
        printf("Program Node with %d global variable declarations, %d function "
               "declaratations\n",
               list_length(node->as.program.declarations),
               list_length(node->as.program.functions));
        break;
    case DECLARATION:
        printf("Declaration Node of data type \'%s\' for %d names\n",
               data_type_to_string(node->as.declaration.d_type),
               list_length(node->as.declaration.names));
        printf("Names:\n");

        head = node->as.declaration.names;
        while (head != NULL) {
            entry = (symtab_entry *)head->data;
            printf("%s with init value ", entry->id);
            switch (entry->as.variable.d_type) {
            case UNDEF_TYPE:
                printf("undef\n");
                break;
            case INT_TYPE:
                printf("%d\n", entry->as.variable.val.ival);
                break;
            case CHAR_TYPE:
                printf("\'%c\'\n", entry->as.variable.val.cval);
                break;
            case FLOAT_TYPE:
            case DOUBLE_TYPE:
                printf("%.2f\n", entry->as.variable.val.fval);
                break;
            case VOID_TYPE:
                printf("void\n");
            }
            head = head->next;
        }
        break;
    case CONSTANT:
        printf("Constant Node of data type \'%s\' with value ",
               data_type_to_string(node->as.constant.d_type));
        switch (node->as.constant.d_type) {
        case UNDEF_TYPE:
            printf("undef\n");
            break;
        case INT_TYPE:
            printf("%d\n", node->as.constant.val.ival);
            break;
        case CHAR_TYPE:
            printf("\'%c\'\n", node->as.constant.val.cval);
            break;
        case FLOAT_TYPE:
        case DOUBLE_TYPE:
            printf("%.2f\n", node->as.constant.val.fval);
            break;
        case VOID_TYPE:
            printf("void\n");
        }
        break;
    case FUNCTION:
        printf(
            "Function Node of function \'%s\' with return type \'%s\' and %d "
            "parameters\n",
            node->as.function.entry->id,
            data_type_to_string(node->as.function.entry->as.function.ret_type),
            list_length(node->as.function.entry->as.function.parameters));
        if (node->as.function.entry->as.function.parameters != NULL) {
            printf("Parameters:\n");
            head = node->as.function.entry->as.function.parameters;
            while (head != NULL) {
                entry = (symtab_entry *)head->data;
                printf("%s of type \'%s\'\n", entry->id,
                       data_type_to_string(entry->as.parameter.d_type));
                head = head->next;
            }
        }
        break;
    case FUNCTION_TAIL:
        printf("Function Tail Node of %d declarations and %d statements\n",
               list_length(node->as.function_tail.declarations),
               list_length(node->as.function_tail.statements));
        break;
    case IF_STATEMENT:
        printf("If Statement Node with %d elseifs and ",
               list_length(node->as.if_statement.else_if_branches));
        if (node->as.if_statement.if_branch == NULL) {
            printf("no else\n");
        } else {
            printf("else\n");
        }
        break;
    case EXPRESSION_BINARY:
        printf("Expression Binary Node of operator type \'%s\'\n",
               operator_type_to_string(node->as.expression_binary.op_type));
        break;
    case EXPRESSION_UNARY:
        printf("Expression Unary Node of operator type \'%s\'\n",
               operator_type_to_string(node->as.expression_unary.op_type));
        break;
    case VARIABLE_REFERENCE:
        printf("Variable Reference Node of variable \'%s\'\n",
               node->as.variable_reference.entry->id);
        break;
    case FUNCTION_CALL:
        printf("Function Call Node of function \'%s\' and %d arguments\n",
               node->as.function_call.entry->id,
               list_length(node->as.function_call.arguments));
        break;
    case ELSE_IF:
        printf("Else If Node\n");
        break;
    case FOR_LOOP:
        printf("For Loop Node\n");
        break;
    case ASSIGNMENT:
        printf("Assignment Node of variable \'%s\'\n",
               node->as.assignment.variable_reference->as.variable_reference
                   .entry->id);
        break;
    case WHILE_LOOP:
        printf("While Loop Node\n");
        break;
    case JUMP_STATEMENT:
        printf("Jump Statement Node of type \'%s\'\n",
               jump_type_to_string(node->as.jump_statement.j_type));
        break;
    case PRINT_STATEMENT:
        printf("Print Statement Node of type \'%s\'\n",
               print_type_to_string(node->as.print_statement.p_type));
        break;
    case INPUT_STATEMENT:
        printf("Input Statement Node of variable \'%s\'\n",
               node->as.input_statement.variable_reference->as
                   .variable_reference.entry->id);
        break;
    case RETURN_STATEMENT:
        printf("Return Statement Node of return type \'%s\'\n",
               data_type_to_string(node->as.return_statement.ret_type));
    }
}

void ast_list_traversal(list_node *list_head) {
    list_node *head;
    head = list_head;
    while (head != NULL) {
        ast_traversal((ast_node *)head->data);
        head = head->next;
    }
}

void ast_traversal(ast_node *node) {
    /* check if empty */
    if (node == NULL) {
        return;
    }

    switch (node->kind) {
    case PROGRAM:
        ast_print_node(node);
        ast_list_traversal(node->as.program.declarations);
        ast_list_traversal(node->as.program.functions);
        ast_traversal(node->as.program.main_function);
        break;
    case DECLARATION:
        ast_print_node(node);
        break;
    case CONSTANT:
        ast_print_node(node);
        break;
    case FUNCTION:
        ast_print_node(node);
        ast_traversal(node->as.function.function_tail);
        break;
    case FUNCTION_TAIL:
        ast_print_node(node);
        ast_list_traversal(node->as.function_tail.declarations);
        ast_list_traversal(node->as.function_tail.statements);
        break;
    case IF_STATEMENT:
        ast_print_node(node);

        printf("Condition:\n");
        ast_traversal(node->as.if_statement.condition);

        printf("If branch:\n");
        ast_list_traversal(node->as.if_statement.if_branch);

        if (node->as.if_statement.else_if_branches != NULL) {
            printf("Else if branches:\n");
            ast_list_traversal(node->as.if_statement.else_if_branches);
        }

        if (node->as.if_statement.else_branch != NULL) {
            printf("Else branch:\n");
            ast_list_traversal(node->as.if_statement.else_branch);
        }
        break;
    case EXPRESSION_BINARY:
        ast_print_node(node);

        printf("Left child:\n");
        ast_traversal(node->as.expression_binary.left);

        printf("Right child:\n");
        ast_traversal(node->as.expression_binary.right);
        break;
    case EXPRESSION_UNARY:
        ast_print_node(node);

        printf("Operand:\n");
        ast_traversal(node->as.expression_unary.operand);
        break;
    case VARIABLE_REFERENCE:
        ast_print_node(node);
        break;
    case FUNCTION_CALL:
        ast_print_node(node);

        printf("Arguments:\n");
        ast_list_traversal(node->as.function_call.arguments);
        break;
    case ELSE_IF:
        ast_print_node(node);

        printf("Condition:\n");
        ast_traversal(node->as.else_if.condition);

        printf("Elseif branch:\n");
        ast_list_traversal(node->as.else_if.else_if_branch);
        break;
    case FOR_LOOP:
        ast_print_node(node);

        printf("Initialize:\n");
        ast_traversal(node->as.for_loop.initialize);

        printf("Condition:\n");
        ast_traversal(node->as.for_loop.condition);

        printf("Increment:\n");
        ast_traversal(node->as.for_loop.increment);

        printf("For branch:\n");
        ast_list_traversal(node->as.for_loop.for_branch);

        break;
    case ASSIGNMENT:
        ast_print_node(node);

        printf("Assigning:\n");
        ast_traversal(node->as.assignment.expression);
        break;
    case WHILE_LOOP:
        ast_print_node(node);

        printf("Condition:\n");
        ast_traversal(node->as.while_loop.condition);

        printf("While branch:\n");
        ast_list_traversal(node->as.while_loop.while_branch);
        break;
    case JUMP_STATEMENT:
        ast_print_node(node);
        break;
    case PRINT_STATEMENT:
        ast_print_node(node);

        printf("Print value:\n");
        switch (node->as.print_statement.p_type) {
        case STRING:
            printf("%s\n", node->as.print_statement.print_value.sval);
            break;
        case EXPRESSION:
            ast_traversal(node->as.print_statement.print_value.expression);
        }
        break;
    case INPUT_STATEMENT:
        ast_print_node(node);
        break;
    case RETURN_STATEMENT:
        ast_print_node(node);

        if (node->as.return_statement.expression != NULL) {
            printf("Returning:\n");
            ast_traversal(node->as.return_statement.expression);
        }
    }
}