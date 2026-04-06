#include "../include/ir.h"
#include "../include/context.h"
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
        intermediate_code_generation_expression_binary(node);
        break;
    case EXPRESSION_UNARY:
        intermediate_code_generation_expression_unary(node);
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
    tac_list_init();
    intermediate_code_generation_list(node->as.program.declarations);
    intermediate_code_generation(node->as.program.main_function);
    intermediate_code_generation_list(node->as.program.functions);
}

void intermediate_code_generation_declaration(ast_node *node) {
    list_node *head;
    symtab_entry *entry;
    operand lhs, rhs;
    operand none = op_none();
    tac t;

    head = node->as.declaration.names;
    while (head != NULL) {
        entry = (symtab_entry *)head->data;

        /* generate assignment for each variable with init value */
        if (entry->as.variable.init_value.d_type != UNDEF_TYPE) {
            lhs = op_var(entry);
            rhs = op_const(ast_constant_init(entry));
            t = tac_create(OP_ASSIGN, lhs, rhs, none);
            tac_list_add(t);
        }
        head = head->next;
    }
}

operand intermediate_code_generation_constant(ast_node *node) {
    return op_const(node);
}

void intermediate_code_generation_function(ast_node *node) {
    /* generate label with function identifier */
    symtab_entry *entry = node->as.function.entry;
    operand label = op_label(entry->id);
    operand none = op_none();
    tac t = tac_create(OP_LABEL, label, none, none);
    tac_list_add(t);

    /* generate code for function tail */
    enter_local_scope(entry->id);
    intermediate_code_generation(node->as.function.function_tail);
    hide_current_scope();
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

operand intermediate_code_generation_expression_binary(ast_node *node) {
    operator_type op_type;
    op_code op;
    operand arg1, arg2, result;
    tac t;
    op_type = node->as.expression_binary.op_type;
    op = operator_type_to_op_code(op_type);
    arg1 = intermediate_code_generation_expression(
        node->as.expression_binary.left);
    arg2 = intermediate_code_generation_expression(
        node->as.expression_binary.right);
    result =
        op_temp(new_temporary(node->lineno, node->as.expression_binary.d_type));
    tac_create(op, result, arg1, arg2);
    tac_list_add(t);
    return result;
}

operand intermediate_code_generation_expression_unary(ast_node *node) {
    operator_type op_type;
    op_code op;
    operand arg, result;
    operand none = op_none();
    op_type = node->as.expression_unary.op_type;
    op = operator_type_to_op_code(op_type);
    arg = intermediate_code_generation_expression(
        node->as.expression_unary.operand);
    switch (op_type) {
    /* postfix inc/dec perform operation but return the original
     * value for the surrounding expression */
    case POST_INC:
    case POST_DEC:
        result = op_temp(
            new_temporary(node->lineno, node->as.expression_unary.d_type));
        tac_list_add(tac_create(OP_ASSIGN, result, arg, none));
        tac_list_add(tac_create(op, arg, none, none));
        return arg;
    /* prefix inc/dec performs operation and returns the result
     * for the surrounding expression */
    case PRE_INC:
    case PRE_DEC:
        tac_list_add(tac_create(op, arg, op_none(), op_none()));
        return arg;
    /* unary plus yields no operation and simply returns the original value
     * for the surrounding expression */
    case UNARY_PLUS:
        return arg;
    /* unary minus performs operation and returns the result
     * for the surrounding expression */
    case UNARY_MINUS:
        result = op_temp(
            new_temporary(node->lineno, node->as.expression_unary.d_type));
        tac_list_add(tac_create(op, result, arg, op_none()));
        return result;
    default:
        return op_label("_error");
    }
}

operand intermediate_code_generation_variable_reference(ast_node *node) {
    symtab_entry *entry = node->as.variable_reference.entry;
    return op_var(entry);
}

operand intermediate_code_generation_function_call(ast_node *node) {
    list_node *head;
    ast_node *argument;
    operand arg;
    operand none = op_none();

    /* function call arguments */
    head = node->as.function_call.arguments;
    while (head != NULL) {
        argument = (ast_node *)head->data;
        arg = intermediate_code_generation_expression(argument);
        tac_list_add(tac_create(OP_ARG, arg, op_none(), op_none()));
        head = head->next;
    }

    /* perform function call */
    tac_list_add(tac_create(OP_CALL, op_var(node->as.function_call.entry),
                            op_none(), op_none()));

    /* retrieve return value (when there is one) */
    data_type ret_type = node->as.function_call.entry->as.function.ret_type;

    if ((ret_type != UNDEF_TYPE) && (ret_type != VOID_TYPE)) {
        operand result = op_temp(new_temporary(node->lineno, ret_type));
        tac_list_add(tac_create(OP_GETRET, result, op_none(), op_none()));
        return result;
    }

    return none;
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
    operand arg;
    operand none = op_none();
    tac t;
    switch (p_type) {
    case EXPRESSION:
        arg = intermediate_code_generation_expression(
            node->as.print_statement.print_value.expression);
        break;
    case STRING:
        arg = op_string(node->as.print_statement.print_value.sval);
    }
    t = tac_create(OP_PRINT, arg, none, none);
    tac_list_add(t);
}

void intermediate_code_generation_input_statement(ast_node *node) {
    operand arg = intermediate_code_generation_variable_reference(
        node->as.input_statement.variable_reference);
    tac t = tac_create(OP_INPUT, arg, op_none(), op_none());
    tac_list_add(t);
}

void intermediate_code_generation_return_statement(ast_node *node) {
    ast_node *expression = node->as.return_statement.expression;
    operand none = op_none();
    tac t;
    if (expression != NULL) {
        operand arg = intermediate_code_generation_expression(expression);
        t = tac_create(OP_RETV, arg, none, none);
    } else {
        t = tac_create(OP_RET, none, none, none);
    }
    tac_list_add(t);
}

/* ---------------------HELPER FUNCTIONS-------------------- */

operand intermediate_code_generation_expression(ast_node *node) {
    switch (node->kind) {
    case CONSTANT:
        return intermediate_code_generation_constant(node);
    case EXPRESSION_BINARY:
        return intermediate_code_generation_expression_binary(node);
    case EXPRESSION_UNARY:
        return intermediate_code_generation_expression_unary(node);
    case VARIABLE_REFERENCE:
        return intermediate_code_generation_variable_reference(node);
    case FUNCTION_CALL:
        return intermediate_code_generation_function_call(node);
    default:
        return op_none();
    }
}

op_code operator_type_to_op_code(operator_type op_type) {
    switch (op_type) {
    case NO_OP:
        return OP_NOP;
    case ASSIGN:
        return OP_ASSIGN;
    case INC:
        return OP_INC;
    case DEC:
        return OP_DEC;
    case PRE_INC:
        return OP_INC;
    case PRE_DEC:
        return OP_DEC;
    case POST_INC:
        return OP_INC;
    case POST_DEC:
        return OP_DEC;
    case ADD:
        return OP_ADD;
    case SUB:
        return OP_SUB;
    case MUL:
        return OP_MUL;
    case DIV:
        return OP_DIV;
    case REM:
        return OP_REM;
    case UNARY_PLUS:
        return OP_NOP;
    case UNARY_MINUS:
        return OP_NEG;
    case OR:
        return OP_OR;
    case AND:
        return OP_AND;
    case NOT:
        return OP_NOT;
    case EQUAL:
        return OP_EQ;
    case NOT_EQUAL:
        return OP_NEQ;
    case GREATER:
        return OP_GT;
    case LESS:
        return OP_LT;
    case GREATER_EQUAL:
        return OP_GE;
    case LESS_EQUAL:
        return OP_LE;
    }
    return OP_NOP;
}

symtab_entry *new_temporary(int lineno, data_type d_type) {
    static int temp_count = 0;
    char *id = (char *)malloc(15 * sizeof(char));
    sprintf(id, "_tmp%d", temp_count);
    temp_count++;
    return insert_temporary_entry(id, lineno, d_type);
}