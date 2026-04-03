#include "../include/semantics.h"

/* ------------------------LOOP DEPTH----------------------- */

int loop_depth = 0;

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
        node = (ast_node *)head->data;
        semantic_analysis(node);
        head = head->next;
    }
}

void semantic_analysis_program(ast_node *node) {
    printf("Starting semantic analysis of program...\n");
    semantic_analysis_list(node->as.program.declarations);
    semantic_analysis_list(node->as.program.functions);
    semantic_analysis(node->as.program.main_function);
}

void semantic_analysis_declaration(ast_node *node) {
    verify_no_redeclaration_of_names(node->as.declaration.names, node->lineno);
    set_declaration_names_type(node->as.declaration.d_type,
                               node->as.declaration.names);
    verify_declaration_names_init_value(node->as.declaration.names);
}

void semantic_analysis_constant(ast_node *node) {
    printf("Constant Node of data type \'%s\' used in line no. %d\n",
           data_type_to_string(node->as.constant.d_type), node->lineno);
}

void semantic_analysis_function(ast_node *node) {
    symtab_entry *entry = node->as.function.entry;
    verify_no_redeclaration_of_names(entry->as.function.parameters,
                                     node->lineno);
    enter_local_scope(entry->id);
    semantic_analysis(node->as.function.function_tail);
    hide_current_scope();
}

void semantic_analysis_function_tail(ast_node *node) {
    semantic_analysis_list(node->as.function_tail.declarations);
    semantic_analysis_list(node->as.function_tail.statements);
}

void semantic_analysis_if_statement(ast_node *node) {
    semantic_analysis(node->as.if_statement.condition);
    semantic_analysis_list(node->as.if_statement.if_branch);
    semantic_analysis_list(node->as.if_statement.else_if_branches);
    semantic_analysis_list(node->as.if_statement.else_branch);
}

void semantic_analysis_expresssion_binary(ast_node *node) {
    semantic_analysis(node->as.expression_binary.left);
    semantic_analysis(node->as.expression_binary.right);

    data_type d_type = expression_data_type(node);

    printf("Result data type of binary expression in line no. %d is \'%s\'\n",
           node->lineno, data_type_to_string(d_type));
}

void semantic_analysis_expresssion_unary(ast_node *node) {
    semantic_analysis(node->as.expression_unary.operand);

    data_type d_type = expression_data_type(node);

    printf("Result data type unary expression in line no. %d is \'%s\'\n",
           node->lineno, data_type_to_string(d_type));
}

void semantic_analysis_variable_reference(ast_node *node) {
    symtab_entry *entry = node->as.variable_reference.entry;

    printf("Reference of variable \'%s\' in line no. %d is in scope \'%s\'\n",
           entry->id, node->lineno, entry->scope->id);

    verify_variable_declaration_before_use(entry, node->lineno);
}

void semantic_analysis_function_call(ast_node *node) {
    semantic_analysis_list(node->as.function_call.arguments);
}

void semantic_analysis_else_if(ast_node *node) {
    semantic_analysis(node->as.else_if.condition);
    semantic_analysis_list(node->as.else_if.else_if_branch);
}

void semantic_analysis_for_loop(ast_node *node) {
    loop_depth++;

    semantic_analysis(node->as.for_loop.initialize);
    semantic_analysis(node->as.for_loop.condition);
    semantic_analysis(node->as.for_loop.increment);
    semantic_analysis_list(node->as.for_loop.for_branch);

    loop_depth--;
}

void semantic_analysis_assignment(ast_node *node) {
    printf("Semantic analysis of assignment node in line no. %d\n",
           node->lineno);

    semantic_analysis(node->as.assignment.variable_reference);
    semantic_analysis(node->as.assignment.expression);

    data_type lhs_dtype = get_data_type(node->as.assignment.variable_reference
                                            ->as.variable_reference.entry->id);
    data_type rhs_dtype = expression_data_type(node->as.assignment.expression);

    printf("LHS data type is \'%s\'\n", data_type_to_string(lhs_dtype));
    printf("RHS data type is \'%s\'\n", data_type_to_string(rhs_dtype));

    switch (verify_assignment_dtype_compatible(
        lhs_dtype, rhs_dtype,
        node->as.assignment.expression->kind == CONSTANT)) {
    /* not compatible*/
    case 0:
        printf("Incompatible Types!\n");
        break;
    /* same type */
    case 1:
        printf("Types are the same!\n");
        break;
    /* compatible type */
    case 2:
        printf("Compatible Types!\n");
    }
}

void semantic_analysis_while_loop(ast_node *node) {
    loop_depth++;

    semantic_analysis(node->as.while_loop.condition);
    semantic_analysis_list(node->as.while_loop.while_branch);

    loop_depth--;
}

void semantic_analysis_jump_statement(ast_node *node) {
    printf("Jump Statement Node of type \'%s\'\n",
           jump_type_to_string(node->as.jump_statement.j_type));

    /* check if jump statement is inside of loop */
    if (loop_depth) {
        printf("Jump Statement inside of loop!\n");
    } else {
        printf("Jump Statement not inside of loop!\n");
    }
}

void semantic_analysis_print_statement(ast_node *node) {
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
    semantic_analysis(node->as.input_statement.variable_reference);
    data_type d_type =
        get_data_type(node->as.input_statement.variable_reference->as
                          .variable_reference.entry->id);
    printf("The data type of the input is: \'%s\',",
           data_type_to_string(d_type));
}

void semantic_analysis_return_statement(ast_node *node) {
    set_return_statement_ret_type(node);
    semantic_analysis(node->as.return_statement.expression);
    verify_return_statement_ret_type(node);
}

/* ---------------------HELPER FUNCTIONS-------------------- */

void verify_no_redeclaration_of_names(list_node *names,
                                      int declaration_lineno) {
    list_node *head = names;
    symtab_entry *entry;
    int first_lineno;

    /* function without parameters case */
    if (head == NULL) {
        return;
    }

    while (head != NULL) {
        entry = (symtab_entry *)head->data;

        first_lineno = *((int *)entry->lines->data);

        if (declaration_lineno != first_lineno) {
            printf("Variable \'%s\' gets redeclared in line no. %d\n",
                   entry->id, declaration_lineno);
            return;
        }

        head = head->next;
    }

    printf("No redeclaration of variable \'%s\' in line no. %d\n", entry->id,
           declaration_lineno);
}

void set_declaration_names_type(data_type d_type, list_node *names) {
    list_node *head = names;
    symtab_entry *entry;
    while (head != NULL) {
        entry = (symtab_entry *)head->data;
        printf("Set type of variable \'%s\' to \'%s\'\n", entry->id,
               data_type_to_string(d_type));
        entry->as.variable.d_type = d_type;
        head = head->next;
    }
}

int verify_assignment_dtype_compatible(data_type lhs_dtype, data_type rhs_dtype,
                                       int rhs_is_constant) {
    /*
     * return value meaning
     * 0: not compatible
     * 1: same type
     * 2: compatible type
     */

    /* types the same */
    if (lhs_dtype == rhs_dtype) {
        return 1;
    }
    /* special case - T_FCONST is always double - float is compatible */
    else if (rhs_dtype == DOUBLE_TYPE && lhs_dtype == FLOAT_TYPE) {
        /* if expression is constant node */
        if (rhs_is_constant) {
            return 1;
        }
        /* if expression is not a constant node */
        else {
            return 0;
        }

    }
    /* types NOT the same */
    else {
        data_type prom_type = promote_data_type(rhs_dtype, lhs_dtype);

        /* type promotion possible */
        if (prom_type == lhs_dtype) {
            return 2;
        }
        /* type promotion not possible */
        else {
            return 0;
        }
    }
}

void verify_declaration_names_init_value(list_node *names) {
    list_node *head;
    symtab_entry *entry;

    data_type var_type;
    data_type init_type;

    head = names;
    while (head != NULL) {
        entry = (symtab_entry *)head->data;

        var_type = entry->as.variable.d_type;
        init_type = entry->as.variable.init_value.d_type;

        /* initialization type is UNDEF_TYPE -> there is no init value */
        if (init_type == UNDEF_TYPE) {
            printf("Declaration of variable \'%s\' of type \'%s\' has no "
                   "initialization value\n",
                   entry->id, data_type_to_string(var_type));
        } else {
            switch (
                verify_assignment_dtype_compatible(var_type, init_type, 1)) {
            /* not compatible */
            case 0:
                printf("Declaration of variable \'%s\' of type \'%s\' has "
                       "initialization value of incompatible type \'%s\'\n",
                       entry->id, data_type_to_string(var_type),
                       data_type_to_string(init_type));
                break;
            /* same type */
            case 1:
                printf("Declaration of variable \'%s\' of type \'%s\' has "
                       "initialization value of same type\n",
                       entry->id, data_type_to_string(var_type));
                break;
            /* compatible type */
            case 2:
                printf("Declaration of variable \'%s\' of type \'%s\' has "
                       "initialization value of compatible type \'%s\'\n",
                       entry->id, data_type_to_string(var_type),
                       data_type_to_string(init_type));
            }
        }

        head = head->next;
    }
}

void verify_variable_declaration_before_use(symtab_entry *entry,
                                            int use_lineno) {
    int first_lineno = *((int *)entry->lines->data);

    if (use_lineno == first_lineno) {
        printf("Undeclared variable \'%s\' is used in line no. %d\n", entry->id,
               use_lineno);
    } else {
        printf("Variable \'%s\' declared in line no. %d is correctly used in "
               "line no. %d\n",
               entry->id, first_lineno, use_lineno);
    }
}

void set_return_statement_ret_type(ast_node *node) {
    ast_node *expression = node->as.return_statement.expression;
    if (expression != NULL) {
        data_type ret_type = expression_data_type(expression);
        node->as.return_statement.ret_type = ret_type;
        printf("Set return type of return statement in line no. %d to \'%s\'\n",
               node->lineno, data_type_to_string(ret_type));
    }
    /* Else not required. Type is void in that case. */
}

void verify_return_statement_ret_type(ast_node *node) {
    data_type ret_type = node->as.return_statement.ret_type;
    data_type func_ret_type =
        lookup_symtab_entry(cur_scope->id)->as.function.ret_type;

    printf("Return statement data type is \'%s\'\n",
           data_type_to_string(ret_type));
    printf("Function return type is \'%s\'\n",
           data_type_to_string(func_ret_type));

    /* function has no return value */
    if (func_ret_type == VOID_TYPE) {
        /* return statement has no return value -> correct */
        if (ret_type == VOID_TYPE) {
            printf("Return statement correctly returns no value!\n");
        }
        /* return statement has return value -> incorrect */
        else {
            printf("Return statement incorrectly returns value!\n");
        }
    }
    /* function has return value */
    else {
        /* return statement has no return value -> incorrect */
        if (ret_type == VOID_TYPE) {
            printf("Return statement incorrectly doesn't return value!\n");
        }
        /* return statement has return value */
        else {
            switch (verify_assignment_dtype_compatible(
                func_ret_type, ret_type,
                node->as.return_statement.expression->kind == CONSTANT)) {
            /* not compatible */
            case 0:
                printf("The return value of the return statement is not "
                       "compatible with the function return value!\n");
                break;
            /* same type */
            case 1:
                printf(
                    "Return statement of same type as function return value\n");
                break;
            /* compatible type */
            case 2:
                printf("Return statement has value of compatible type to "
                       "function return value!\n");
            }
        }
    }
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