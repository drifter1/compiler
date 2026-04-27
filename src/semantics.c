#include "../include/semantics.h"
#include "../include/debug.h"
#include "../include/error.h"

/* ------------------RETURN STATEMENT COUNT----------------- */

int return_count = 0;

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
#if SEM_DEBUG
    printf("Starting semantic analysis of program...\n");
#endif
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
#if SEM_DEBUG
    printf("Constant Node of data type \'%s\' used in line no. %d. No semantic "
           "analysis necessary!\n",
           data_type_to_string(node->as.constant.d_type), node->lineno);
#endif
}

void semantic_analysis_function(ast_node *node) {
    symtab_entry *entry = node->as.function.entry;
    int declaration_lineno = get_first_lineno(entry);
    verify_no_redeclaration_of_function_name(entry, node->lineno);
    verify_no_redeclaration_of_names(entry->as.function.parameters,
                                     declaration_lineno);
    enter_local_scope(entry->id);
    semantic_analysis(node->as.function.function_tail);
    hide_current_scope();
}

void semantic_analysis_function_tail(ast_node *node) {
    semantic_analysis_list(node->as.function_tail.declarations);
    semantic_analysis_list(node->as.function_tail.statements);
    verify_return_statement_last(node->as.function_tail.statements);

    /* reset return statement counter */
    return_count = 0;
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

    if (d_type == UNDEF_TYPE || d_type == VOID_TYPE) {
        semantic_analysis_error(
            node->lineno, ERR_BIN_INVALID_OPERANDS,
            data_type_to_string(
                expression_data_type(node->as.expression_binary.left)),
            data_type_to_string(
                expression_data_type(node->as.expression_binary.right)),
            operator_type_to_string(node->as.expression_binary.op_type));
    } else {
        node->as.expression_binary.d_type = d_type;
#if SEM_DEBUG
        printf("Result data type of binary expression of operator type "
               "\'%s\' at line no. %d is \'%s\'\n",
               operator_type_to_string(node->as.expression_binary.op_type),
               node->lineno, data_type_to_string(d_type));
#endif
    }
}

void semantic_analysis_expresssion_unary(ast_node *node) {
    semantic_analysis(node->as.expression_unary.operand);

    data_type d_type = expression_data_type(node);

    if (d_type == UNDEF_TYPE || d_type == VOID_TYPE) {
        semantic_analysis_error(
            node->lineno, ERR_UNARY_INVALID_OPERANDS,
            data_type_to_string(
                expression_data_type(node->as.expression_unary.operand)),
            operator_type_to_string(node->as.expression_unary.op_type));
    } else {
        node->as.expression_unary.d_type = d_type;
#if SEM_DEBUG
        printf("Result data type of unary expression of operator type \'%s\' "
               "at line no. %d is \'%s\'\n",
               operator_type_to_string(node->as.expression_unary.op_type),
               node->lineno, data_type_to_string(d_type));
#endif
    }
}

void semantic_analysis_variable_reference(ast_node *node) {
    symtab_entry *entry = node->as.variable_reference.entry;

#if SEM_DEBUG
    printf("Reference of variable \'%s\' at line no. %d is in scope \'%s\'\n",
           entry->id, node->lineno, entry->scope->id);
#endif

    verify_variable_declaration_before_use(entry, node->lineno);
}

void semantic_analysis_function_call(ast_node *node) {
#if SEM_DEBUG
    printf("Semantic analysis of function call node of function \'%s\' in line "
           "no. %d\n",
           node->as.function_call.entry->id, node->lineno);
#endif

    semantic_analysis_list(node->as.function_call.arguments);

    list_node *arguments = node->as.function_call.arguments;
    list_node *parameters =
        node->as.function_call.entry->as.function.parameters;

    verify_function_call_argument_count(parameters, arguments, node->lineno);
    verify_function_call_argument_types(parameters, arguments, node->lineno);
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
#if SEM_DEBUG
    printf("Semantic analysis of assignment node at line no. %d\n",
           node->lineno);
#endif

    semantic_analysis(node->as.assignment.variable_reference);
    semantic_analysis(node->as.assignment.expression);

    data_type lhs_dtype = get_data_type(
        node->as.assignment.variable_reference->as.variable_reference.entry);
    data_type rhs_dtype = expression_data_type(node->as.assignment.expression);

#if SEM_DEBUG
    printf("LHS data type is \'%s\'\n", data_type_to_string(lhs_dtype));
    printf("RHS data type is \'%s\'\n", data_type_to_string(rhs_dtype));
#endif

    switch (verify_assignment_dtype_compatible(
        lhs_dtype, rhs_dtype,
        node->as.assignment.expression->kind == CONSTANT)) {
    case NOT_COMPATIBLE:
        semantic_analysis_error(node->lineno, ERR_ASSIGN_INCOMPATIBLE,
                                data_type_to_string(rhs_dtype),
                                data_type_to_string(lhs_dtype));
        break;
    case SAME_TYPE:
#if SEM_DEBUG
        printf("Types are the same!\n");
#endif
        break;
    case COMPATIBLE:
#if SEM_DEBUG
        printf("Compatible Types!\n");
#endif
    }
}

void semantic_analysis_while_loop(ast_node *node) {
    loop_depth++;

    semantic_analysis(node->as.while_loop.condition);
    semantic_analysis_list(node->as.while_loop.while_branch);

    loop_depth--;
}

void semantic_analysis_jump_statement(ast_node *node) {
#if SEM_DEBUG
    printf("Jump statement node of type \'%s\'\n",
           jump_type_to_string(node->as.jump_statement.j_type));
#endif

    /* check if jump statement is inside of loop */
    if (!loop_depth) {
        semantic_analysis_error(
            node->lineno, ERR_JUMP_NOT_IN_LOOP,
            jump_type_to_string(node->as.jump_statement.j_type));

    } else {
#if SEM_DEBUG
        printf("Jump statement at line no. %d inside of loop!\n", node->lineno);
#endif
    }
}

void semantic_analysis_print_statement(ast_node *node) {
#if SEM_DEBUG
    printf("Print statement node of type \'%s\'\n",
           print_type_to_string(node->as.print_statement.p_type));
#endif

    data_type d_type;

    switch (node->as.print_statement.p_type) {
    case EXPRESSION:
        semantic_analysis(node->as.print_statement.print_value.expression);
        d_type = expression_data_type(
            node->as.print_statement.print_value.expression);
        if (d_type == UNDEF_TYPE || d_type == VOID_TYPE) {
            semantic_analysis_error(node->lineno, ERR_OUTPUT_TYPE,
                                    data_type_to_string(d_type));
        } else {
#if SEM_DEBUG
            printf("The data type of the output value is: \'%s\'\n",
                   data_type_to_string(d_type));
#endif
        }
        break;
    case STRING:
#if SEM_DEBUG
        printf(
            "The output value is a STRING. No semantic analysis necessary!\n");
#endif
    }
}

void semantic_analysis_input_statement(ast_node *node) {
    semantic_analysis(node->as.input_statement.variable_reference);

#if SEM_DEBUG
    data_type d_type =
        get_data_type(node->as.input_statement.variable_reference->as
                          .variable_reference.entry);
    printf("The data type of the input is: \'%s\'\n",
           data_type_to_string(d_type));
#endif
}

void semantic_analysis_return_statement(ast_node *node) {
    set_return_statement_ret_type(node);
    semantic_analysis(node->as.return_statement.expression);
    verify_return_statement_ret_type(node);

    /* increment return statement counter */
    return_count++;
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

        first_lineno = get_first_lineno(entry);

        if (declaration_lineno != first_lineno) {
            semantic_analysis_error(declaration_lineno, ERR_REDECLARED_VAR,
                                    entry->id);
        }

        head = head->next;
    }

#if SEM_DEBUG
    printf("No redeclaration of identifier \'%s\' at line no. %d\n", entry->id,
           declaration_lineno);
#endif
}

void set_declaration_names_type(data_type d_type, list_node *names) {
    list_node *head = names;
    symtab_entry *entry;
    while (head != NULL) {
        entry = (symtab_entry *)head->data;
#if SEM_DEBUG
        printf("Set type of variable \'%s\' to \'%s\'\n", entry->id,
               data_type_to_string(d_type));
#endif
        entry->as.variable.d_type = d_type;
        head = head->next;
    }
}

dtype_compatibility verify_assignment_dtype_compatible(data_type lhs_dtype,
                                                       data_type rhs_dtype,
                                                       int rhs_is_constant) {
    /* types the same */
    if (lhs_dtype == rhs_dtype) {
        return SAME_TYPE;
    }
    /* special case - T_FCONST is always double - float is compatible */
    else if (rhs_dtype == DOUBLE_TYPE && lhs_dtype == FLOAT_TYPE) {
        /* if expression is constant node */
        if (rhs_is_constant) {
            return SAME_TYPE;
        }
        /* if expression is not a constant node */
        else {
            return NOT_COMPATIBLE;
        }

    }
    /* types NOT the same */
    else {
        data_type prom_type = promote_data_type(rhs_dtype, lhs_dtype);

        /* type promotion possible */
        if (prom_type == lhs_dtype) {
            return COMPATIBLE;
        }
        /* type promotion not possible */
        else {
            return NOT_COMPATIBLE;
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

        int declaration_lineno = get_first_lineno(entry);

        /* initialization type is UNDEF_TYPE -> there is no init value */
        if (init_type == UNDEF_TYPE) {
#if SEM_DEBUG
            printf("Declaration of variable \'%s\' of type \'%s\' has no "
                   "initialization value\n",
                   entry->id, data_type_to_string(var_type));
#endif
        } else {
            switch (
                verify_assignment_dtype_compatible(var_type, init_type, 1)) {
            case NOT_COMPATIBLE:
                semantic_analysis_error(declaration_lineno,
                                        ERR_VAR_INIT_INCOMPATIBLE, entry->id,
                                        data_type_to_string(var_type),
                                        data_type_to_string(init_type));
                break;
            case SAME_TYPE:
#if SEM_DEBUG
                printf("Declaration of variable \'%s\' of type \'%s\' has "
                       "initialization value of same type\n",
                       entry->id, data_type_to_string(var_type));
#endif
                break;
            case COMPATIBLE:
#if SEM_DEBUG
                printf("Declaration of variable \'%s\' of type \'%s\' has "
                       "initialization value of compatible type \'%s\'\n",
                       entry->id, data_type_to_string(var_type),
                       data_type_to_string(init_type));
#endif
            }
        }

        head = head->next;
    }
}

void verify_no_redeclaration_of_function_name(symtab_entry *entry,
                                              int declaration_lineno) {
    int first_lineno;

    first_lineno = get_first_lineno(entry);

    if (declaration_lineno != first_lineno) {
        semantic_analysis_error(declaration_lineno, ERR_REDECLARED_FUNC,
                                entry->id);
    } else {
#if SEM_DEBUG
        printf("No redeclaration of identifier \'%s\' at line no. %d\n",
               entry->id, declaration_lineno);
#endif
    }
}

void verify_return_statement_last(list_node *statements) {
    symtab_entry *entry = lookup_symtab_entry(cur_scope->id);
    data_type ret_type = entry->as.function.ret_type;
    int declaration_lineno = get_first_lineno(entry);

    /* locate last statement node in statement list */
    list_node *head = statements;
    ast_node *statement;
    while (head != NULL) {
        statement = (ast_node *)head->data;
        head = head->next;
    }

    /* function void -> return statement position check is optional */
    if (ret_type == VOID_TYPE) {
        /* check kind of last statement node */
        if (statement->kind == RETURN_STATEMENT) {
#if SEM_DEBUG
            printf("Optional return statement was found at the end of function "
                   "\'%s\' of return type \'%s\'\n",
                   entry->id, data_type_to_string(ret_type));
#endif
        }
    }
    /* function NOT void -> return statement position check is required */
    else {
        /* check kind of last statement node */
        if (statement->kind == RETURN_STATEMENT) {
#if SEM_DEBUG
            printf("Return statement was located at the of function \'%s\' of "
                   "type \'%s\' as required!\n",
                   entry->id, data_type_to_string(ret_type));
#endif
        } else {
            semantic_analysis_error(declaration_lineno, ERR_MISSING_RETURN,
                                    entry->id, data_type_to_string(ret_type));
        }
    }

    /* check return statement count */
    if (return_count > 1) {
        semantic_analysis_error(declaration_lineno, ERR_MULTIPLE_RETURNS,
                                entry->id);
    }
}

void verify_variable_declaration_before_use(symtab_entry *entry,
                                            int use_lineno) {
    int first_lineno = get_first_lineno(entry);

    if (use_lineno == first_lineno) {
        semantic_analysis_error(use_lineno, ERR_UNDECLARED_VAR, entry->id);
    } else {
#if SEM_DEBUG
        printf("Variable \'%s\' declared at line no. %d is correctly used in "
               "line no. %d\n",
               entry->id, first_lineno, use_lineno);
#endif
    }
}

void verify_function_call_argument_count(list_node *parameters,
                                         list_node *arguments, int lineno) {
    int argument_count = list_length(arguments);
    int parameter_count = list_length(parameters);

#if SEM_DEBUG
    printf("Argument count is %d\n", argument_count);
    printf("Parameter count is %d\n", argument_count);
#endif

    if (argument_count != parameter_count) {
        semantic_analysis_error(lineno, ERR_FUNC_ARG_NUM_MISMATCH,
                                argument_count, parameter_count);
    } else {
#if SEM_DEBUG
        printf("Function call arguments are equal to the parameters required "
               "by the function!\n");
#endif
    }
}

void verify_function_call_argument_types(list_node *parameters,
                                         list_node *arguments, int lineno) {
    ast_node *argument;
    symtab_entry *parameter;
    data_type arg_dtype, par_dtype;

    while (arguments != NULL) {
        argument = (ast_node *)arguments->data;
        parameter = (symtab_entry *)parameters->data;

        /* verify type compatibility */
        arg_dtype = expression_data_type(argument);
        par_dtype = parameter->as.parameter.d_type;

        switch (verify_assignment_dtype_compatible(
            par_dtype, arg_dtype, argument->kind == CONSTANT)) {
        case NOT_COMPATIBLE:
            semantic_analysis_error(lineno, ERR_FUNC_ARG_TYPE_MISMATCH,
                                    data_type_to_string(arg_dtype),
                                    parameter->id,
                                    data_type_to_string(par_dtype));
            break;
        case SAME_TYPE:
#if SEM_DEBUG
            printf("Argument for parameter \'%s\' of type "
                   "\'%s\' is of same type!\n",
                   parameter->id, data_type_to_string(par_dtype));
#endif
            break;
        case COMPATIBLE:
#if SEM_DEBUG
            printf("Argument of type \'%s\' for parameter \'%s\' of type "
                   "\'%s\' is of compatible type!\n",
                   data_type_to_string(arg_dtype), parameter->id,
                   data_type_to_string(par_dtype));
#endif
            break;
        }

        arguments = arguments->next;
        parameters = parameters->next;
    }
}

void set_return_statement_ret_type(ast_node *node) {
    ast_node *expression = node->as.return_statement.expression;
    if (expression != NULL) {
        data_type ret_type = expression_data_type(expression);
        node->as.return_statement.ret_type = ret_type;
#if SEM_DEBUG
        printf("Set return type of return statement in line no. %d to "
               "\'%s\'\n",
               node->lineno, data_type_to_string(ret_type));
#endif
    }
    /* Else not required. Type is void in that case. */
}

void verify_return_statement_ret_type(ast_node *node) {
    data_type ret_type = node->as.return_statement.ret_type;
    data_type func_ret_type =
        lookup_symtab_entry(cur_scope->id)->as.function.ret_type;

#if SEM_DEBUG
    printf("Return statement data type is \'%s\'\n",
           data_type_to_string(ret_type));
    printf("Function return type is \'%s\'\n",
           data_type_to_string(func_ret_type));
#endif

    /* function has no return value */
    if (func_ret_type == VOID_TYPE) {
        /* return statement has no return value -> correct */
        if (ret_type == VOID_TYPE) {
#if SEM_DEBUG
            printf("Return statement correctly returns no value!\n");
#endif
        }
        /* return statement has return value -> incorrect */
        else {
            semantic_analysis_error(node->lineno, ERR_RETURN_VALUE_IN_VOID);
        }
    }
    /* function has return value */
    else {
        /* return statement has no return value -> incorrect */
        if (ret_type == VOID_TYPE) {
            semantic_analysis_error(node->lineno, ERR_RETURN_NO_VALUE,
                                    data_type_to_string(func_ret_type));
        }
        /* return statement has return value */
        else {
            switch (verify_assignment_dtype_compatible(
                func_ret_type, ret_type,
                node->as.return_statement.expression->kind == CONSTANT)) {
            case NOT_COMPATIBLE:
                semantic_analysis_error(node->lineno, ERR_RETURN_TYPE_MISMATCH,
                                        data_type_to_string(ret_type),
                                        data_type_to_string(func_ret_type));
                break;
            case SAME_TYPE:
#if SEM_DEBUG
                printf("Return statement of same type as function return "
                       "value\n");
#endif
                break;
            case COMPATIBLE:
#if SEM_DEBUG
                printf("Return statement has value of compatible type to "
                       "function return value!\n");
#endif
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
        return get_data_type(node->as.variable_reference.entry);
    case CONSTANT:
        return node->as.constant.d_type;
    case FUNCTION_CALL:
        return get_data_type(node->as.function_call.entry);
    default:
        return UNDEF_TYPE;
    }
}