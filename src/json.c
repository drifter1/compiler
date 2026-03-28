#include "../include/json.h"
#include <jansson.h>

json_t *json_construct_ast_node(ast_node *node) {
    json_t *json_ast_node = json_object();

    json_object_set(json_ast_node, "kind",
                    json_string(ast_node_kind_to_string(node->kind)));
    json_object_set(json_ast_node, "lineno", json_integer(node->lineno));

    switch (node->kind) {
    case PROGRAM:
        json_object_set(
            json_ast_node, "declarations",
            json_construct_ast_node_list(node->as.program.declarations));
        json_object_set(
            json_ast_node, "functions",
            json_construct_ast_node_list(node->as.program.functions));
        json_object_set(
            json_ast_node, "main_function",
            json_construct_ast_node(node->as.program.main_function));
        break;
    case DECLARATION:
        json_object_set(
            json_ast_node, "d_type",
            json_string(data_type_to_string(node->as.declaration.d_type)));
        json_object_set(json_ast_node, "names",
                        json_construct_names(node->as.declaration.names));
        break;
    case CONSTANT:
        json_object_set(
            json_ast_node, "d_type",
            json_string(data_type_to_string(node->as.constant.d_type)));

        char cval[1];
        switch (node->as.constant.d_type) {
        case UNDEF_TYPE:
            json_object_set(json_ast_node, "val", json_null());
            break;
        case INT_TYPE:
            json_object_set(json_ast_node, "val",
                            json_integer(node->as.constant.val.ival));
            break;
        case CHAR_TYPE:
            cval[0] = node->as.constant.val.cval;
            json_object_set(json_ast_node, "val", json_string(cval));
            break;
        case FLOAT_TYPE:
        case DOUBLE_TYPE:
            json_object_set(json_ast_node, "val",
                            json_real(node->as.constant.val.fval));
            break;
        case VOID_TYPE:
            json_object_set(json_ast_node, "val", json_null());
        }
        break;
    case FUNCTION:
        json_object_set(json_ast_node, "entry",
                        json_construct_symtab_entry(node->as.function.entry));
        json_object_set(
            json_ast_node, "function_tail",
            json_construct_ast_node(node->as.function.function_tail));
        break;
    case FUNCTION_TAIL:
        json_object_set(
            json_ast_node, "declarations",
            json_construct_ast_node_list(node->as.function_tail.declarations));
        json_object_set(
            json_ast_node, "statements",
            json_construct_ast_node_list(node->as.function_tail.statements));
        break;
    case IF_STATEMENT:
        json_object_set(
            json_ast_node, "condition",
            json_construct_ast_node(node->as.if_statement.condition));
        json_object_set(
            json_ast_node, "if_branch",
            json_construct_ast_node_list(node->as.if_statement.if_branch));
        json_object_set(json_ast_node, "else_if_branches",
                        json_construct_ast_node_list(
                            node->as.if_statement.else_if_branches));
        json_object_set(
            json_ast_node, "else_branch",
            json_construct_ast_node_list(node->as.if_statement.else_branch));
        break;
    case EXPRESSION_BINARY:
        json_object_set(
            json_ast_node, "left",
            json_construct_ast_node(node->as.expression_binary.left));
        json_object_set(json_ast_node, "op_type",
                        json_string(operator_type_to_string(
                            node->as.expression_binary.op_type)));
        json_object_set(
            json_ast_node, "right",
            json_construct_ast_node(node->as.expression_binary.right));
        break;
    case EXPRESSION_UNARY:
        json_object_set(
            json_ast_node, "operand",
            json_construct_ast_node(node->as.expression_unary.operand));
        json_object_set(json_ast_node, "op_type",
                        json_string(operator_type_to_string(
                            node->as.expression_unary.op_type)));
        break;
    case VARIABLE_REFERENCE:
        json_object_set(
            json_ast_node, "entry",
            json_construct_symtab_entry(node->as.variable_reference.entry));
        break;
    case FUNCTION_CALL:
        json_object_set(
            json_ast_node, "entry",
            json_construct_symtab_entry(node->as.function_call.entry));
        json_object_set(
            json_ast_node, "arguments",
            json_construct_ast_node_list(node->as.function_call.arguments));
        break;
    case ELSE_IF:
        json_object_set(json_ast_node, "condition",
                        json_construct_ast_node(node->as.else_if.condition));
        json_object_set(
            json_ast_node, "else_if_branch",
            json_construct_ast_node_list(node->as.else_if.else_if_branch));
        break;
    case FOR_LOOP:
        json_object_set(json_ast_node, "initialize",
                        json_construct_ast_node(node->as.for_loop.initialize));
        json_object_set(json_ast_node, "condition",
                        json_construct_ast_node(node->as.for_loop.condition));
        json_object_set(json_ast_node, "increment",
                        json_construct_ast_node(node->as.for_loop.increment));
        json_object_set(
            json_ast_node, "for_branch",
            json_construct_ast_node_list(node->as.for_loop.for_branch));
        break;
    case ASSIGNMENT:
        json_object_set(
            json_ast_node, "variable_reference",
            json_construct_ast_node(node->as.assignment.variable_reference));
        json_object_set(
            json_ast_node, "expression",
            json_construct_ast_node(node->as.assignment.expression));
        break;
    case WHILE_LOOP:
        json_object_set(json_ast_node, "condition",
                        json_construct_ast_node(node->as.while_loop.condition));
        json_object_set(
            json_ast_node, "while_branch",
            json_construct_ast_node_list(node->as.while_loop.while_branch));
        break;
    case JUMP_STATEMENT:
        json_object_set(
            json_ast_node, "j_type",
            json_string(jump_type_to_string(node->as.jump_statement.j_type)));
        break;
    case PRINT_STATEMENT:
        json_object_set(
            json_ast_node, "p_type",
            json_string(print_type_to_string(node->as.print_statement.p_type)));

        switch (node->as.print_statement.p_type) {
        case EXPRESSION:
            json_object_set(
                json_ast_node, "print_value",
                json_construct_ast_node(
                    node->as.print_statement.print_value.expression));
            break;
        case STRING:
            json_object_set(
                json_ast_node, "print_value",
                json_string(node->as.print_statement.print_value.sval));
        }
        break;
    case INPUT_STATEMENT:
        json_object_set(json_ast_node, "variable_reference",
                        json_construct_ast_node(
                            node->as.input_statement.variable_reference));
        break;
    case RETURN_STATEMENT:
        json_object_set(json_ast_node, "ret_type",
                        json_string(data_type_to_string(
                            node->as.return_statement.ret_type)));

        if (node->as.return_statement.expression == NULL) {
            json_object_set(json_ast_node, "expression", json_null());
        } else {
            json_object_set(
                json_ast_node, "expression",
                json_construct_ast_node(node->as.return_statement.expression));
        }
        break;
    }

    return json_ast_node;
}

json_t *json_construct_ast_node_list(list_node *list_head) {
    json_t *ast_node_list = json_array();

    list_node *head;
    ast_node *node;

    head = list_head;
    while (head != NULL) {
        node = (struct ast_node *)head->data;

        json_array_append(ast_node_list, json_construct_ast_node(node));

        head = head->next;
    }

    return ast_node_list;
}

json_t *json_construct_names(list_node *names) {
    json_t *json_names = json_array();

    list_node *head;
    symtab_entry *entry;

    head = names;
    while (head != NULL) {
        entry = (symtab_entry *)head->data;

        json_array_append(json_names, json_construct_symtab_entry(entry));

        head = head->next;
    }

    return json_names;
}

json_t *json_construct_symtab_entry(symtab_entry *entry) {
    json_t *json_symtab_entry = json_object();

    json_object_set(json_symtab_entry, "kind",
                    json_string(symtab_entry_kind_to_string(entry->kind)));
    json_object_set(json_symtab_entry, "id", json_string(entry->id));
    json_object_set(json_symtab_entry, "len", json_integer(entry->len));
    json_object_set(json_symtab_entry, "scope",
                    json_construct_scope(entry->scope));
    json_object_set(json_symtab_entry, "lines",
                    json_construct_lines(entry->lines));

    if (entry->next == NULL) {
        json_object_set(json_symtab_entry, "next", json_null());
    } else {
        json_object_set(json_symtab_entry, "next",
                        json_construct_symtab_entry(entry->next));
    }

    switch (entry->kind) {
    case VARIABLE_ENTRY:
        json_object_set(
            json_symtab_entry, "d_type",
            json_string(data_type_to_string(entry->as.variable.d_type)));
        json_object_set(
            json_symtab_entry, "init_value",
            json_construct_init_value(entry->as.variable.init_value.d_type,
                                      entry->as.variable.init_value.val));
        break;
    case PARAMETER_ENTRY:
        json_object_set(
            json_symtab_entry, "d_type",
            json_string(data_type_to_string(entry->as.parameter.d_type)));
        break;
    case FUNCTION_ENTRY:
        json_object_set(
            json_symtab_entry, "ret_type",
            json_string(data_type_to_string(entry->as.function.ret_type)));
        json_object_set(
            json_symtab_entry, "parameters",
            json_construct_parameters(entry->as.function.parameters));
    }

    return json_symtab_entry;
}

json_t *json_construct_scope(scope *scope) {
    json_t *json_scope = json_object();

    if (scope->parent == NULL) {
        json_object_set(json_scope, "parent", json_null());
    } else {
        json_object_set(json_scope, "parent",
                        json_construct_scope(scope->parent));
    }

    json_object_set(json_scope, "kind",
                    json_string(scope_kind_to_string(scope->kind)));
    json_object_set(json_scope, "id", json_string(scope->id));
    json_object_set(json_scope, "visibility",
                    json_string(visibility_kind_to_string(scope->visibility)));

    return json_scope;
}

json_t *json_construct_lines(list_node *lines) {
    json_t *json_lines = json_array();

    list_node *head;
    int lineno;

    head = lines;
    while (head != NULL) {
        lineno = *((int *)head->data);

        json_array_append(json_lines, json_integer(lineno));

        head = head->next;
    }

    return json_lines;
}

json_t *json_construct_init_value(data_type d_type, value val) {
    json_t *json_init_value = json_object();

    json_object_set(json_init_value, "d_type",
                    json_string(data_type_to_string(d_type)));

    char cval[1];
    switch (d_type) {
    case UNDEF_TYPE:
        json_object_set(json_init_value, "val", json_null());
        break;
    case INT_TYPE:
        json_object_set(json_init_value, "val", json_integer(val.ival));
        break;
    case CHAR_TYPE:
        cval[0] = val.cval;
        json_object_set(json_init_value, "val", json_string(cval));
        break;
    case FLOAT_TYPE:
    case DOUBLE_TYPE:
        json_object_set(json_init_value, "val", json_real(val.fval));
        break;
    case VOID_TYPE:
        json_object_set(json_init_value, "val", json_null());
    }

    return json_init_value;
}

json_t *json_construct_parameters(list_node *parameters) {
    json_t *json_parameters = json_array();

    list_node *head;
    symtab_entry *parameter;

    head = parameters;
    while (head != NULL) {
        parameter = (symtab_entry *)head->data;

        json_array_append(json_parameters,
                          json_construct_symtab_entry(parameter));

        head = head->next;
    }

    return json_parameters;
}