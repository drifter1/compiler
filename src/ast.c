#include "../include/compiler.h"
#include <stdlib.h>

/* ---------------------AST STRUCTURE----------------------- */

ast_node *ast;

/* ------------------AST NODE MANAGEMENT-------------------- */

ast_node *new_ast_node(void) { return (ast_node *)malloc(sizeof(ast_node)); }

ast_node *ast_program(list_node *declarations, list_node *functions,
                      ast_node *main_function) {
    ast_node *v = new_ast_node();

    v->kind = PROGRAM;
    v->lineno = yylineno;

    v->as.program.declarations = declarations;
    v->as.program.functions = functions;
    v->as.program.main_function = main_function;

    return v;
}

ast_node *ast_declaration(data_type d_type, list_node *names) {
    ast_node *v = new_ast_node();

    v->kind = DECLARATION;
    v->lineno = yylineno;

    v->as.declaration.d_type = d_type;
    v->as.declaration.names = names;

    return v;
}

ast_node *ast_constant(data_type d_type, value val) {
    ast_node *v = new_ast_node();

    v->kind = CONSTANT;
    v->lineno = yylineno;

    v->as.constant.d_type = d_type;
    v->as.constant.val = val;

    return v;
}

ast_node *ast_function(symtab_entry *entry, ast_node *function_tail) {
    ast_node *v = new_ast_node();

    v->kind = FUNCTION;
    v->lineno = yylineno;

    v->as.function.entry = entry;
    v->as.function.function_tail = function_tail;

    return v;
}

ast_node *ast_function_tail(list_node *declarations, list_node *statements) {
    ast_node *v = new_ast_node();

    v->kind = FUNCTION_TAIL;
    v->lineno = yylineno;

    v->as.function_tail.declarations = declarations;
    v->as.function_tail.statements = statements;

    return v;
}

ast_node *ast_if_statement(ast_node *condition, list_node *if_branch,
                           list_node *else_if_branches,
                           list_node *else_branch) {
    ast_node *v = new_ast_node();

    v->kind = IF_STATEMENT;
    v->lineno = yylineno;

    v->as.if_statement.condition = condition;
    v->as.if_statement.if_branch = if_branch;
    v->as.if_statement.else_if_branches = else_if_branches;
    v->as.if_statement.else_branch = else_branch;

    return v;
}

ast_node *ast_expression_binary(ast_node *left, operator_type op_type,
                                ast_node *right) {
    ast_node *v = new_ast_node();

    v->kind = EXPRESSION_BINARY;
    v->lineno = yylineno;

    v->as.expression_binary.left = left;
    v->as.expression_binary.op_type = op_type;
    v->as.expression_binary.right = right;

    return v;
}

ast_node *ast_expression_unary(ast_node *operand, operator_type op_type,
                               fixity_type fixity) {
    ast_node *v = new_ast_node();

    v->kind = EXPRESSION_UNARY;
    v->lineno = yylineno;

    v->as.expression_unary.operand = operand;
    v->as.expression_unary.op_type =
        ast_expression_unary_op_type(op_type, fixity);

    return v;
}

ast_node *ast_variable_reference(symtab_entry *entry) {
    ast_node *v = new_ast_node();

    v->kind = VARIABLE_REFERENCE;
    v->lineno = yylineno;

    v->as.variable_reference.entry = entry;

    return v;
}

ast_node *ast_function_call(symtab_entry *entry, list_node *arguments) {
    ast_node *v = new_ast_node();

    v->kind = FUNCTION_CALL;
    v->lineno = yylineno;

    v->as.function_call.entry = entry;
    v->as.function_call.arguments = arguments;

    return v;
}

ast_node *ast_else_if(ast_node *condition, list_node *else_if_branch) {
    ast_node *v = new_ast_node();

    v->kind = ELSE_IF;
    v->lineno = yylineno;

    v->as.else_if.condition = condition;
    v->as.else_if.else_if_branch = else_if_branch;

    return v;
}

ast_node *ast_for_loop(ast_node *initialize, ast_node *condition,
                       ast_node *increment, list_node *for_branch) {
    ast_node *v = new_ast_node();

    v->kind = FOR_LOOP;
    v->lineno = yylineno;

    v->as.for_loop.initialize = initialize;
    v->as.for_loop.condition = condition;
    v->as.for_loop.increment = increment;
    v->as.for_loop.for_branch = for_branch;

    return v;
}

ast_node *ast_assignment(ast_node *variable_reference, ast_node *expression) {
    ast_node *v = new_ast_node();

    v->kind = ASSIGNMENT;
    v->lineno = yylineno;

    v->as.assignment.variable_reference = variable_reference;
    v->as.assignment.expression = expression;

    return v;
}

ast_node *ast_while_loop(ast_node *condition, list_node *while_branch) {
    ast_node *v = new_ast_node();

    v->kind = WHILE_LOOP;
    v->lineno = yylineno;

    v->as.while_loop.condition = condition;
    v->as.while_loop.while_branch = while_branch;

    return v;
}

ast_node *ast_jump_statement(jump_type j_type) {
    ast_node *v = new_ast_node();

    v->kind = JUMP_STATEMENT;
    v->lineno = yylineno;

    v->as.jump_statement.j_type = j_type;

    return v;
}

ast_node *ast_print_statement(print_type p_type, char *sval,
                              ast_node *expression) {
    ast_node *v = new_ast_node();

    v->kind = PRINT_STATEMENT;
    v->lineno = yylineno;

    v->as.print_statement.p_type = p_type;

    switch (p_type) {
    case EXPRESSION:
        v->as.print_statement.print_value.expression = expression;
        break;
    case STRING:
        v->as.print_statement.print_value.sval = sval;
    }

    return v;
}

ast_node *ast_input_statement(ast_node *variable_reference) {
    ast_node *v = new_ast_node();

    v->kind = INPUT_STATEMENT;
    v->lineno = yylineno;

    v->as.input_statement.variable_reference = variable_reference;

    return v;
}

ast_node *ast_return_statement(data_type ret_type, ast_node *expression) {
    ast_node *v = new_ast_node();

    v->kind = RETURN_STATEMENT;
    v->lineno = yylineno;

    v->as.return_statement.ret_type = ret_type;
    v->as.return_statement.expression = expression;

    return v;
}

/* --------------------AST NODE HELPERS--------------------- */

operator_type ast_expression_unary_op_type(operator_type op_type,
                                           fixity_type fixity) {
    switch (op_type) {
    case INC:
        switch (fixity) {
        case PREFIX:
            return PRE_INC;
            break;
        case POSTFIX:
            return POST_INC;
        }
        break;
    case DEC:
        switch (fixity) {
        case PREFIX:
            return PRE_DEC;
            break;
        case POSTFIX:
            return POST_DEC;
        }
        break;
    case ADD:
        return UNARY_PLUS;
        break;
    case SUB:
        return UNARY_MINUS;
        break;
    default:
        return op_type;
    }

    return op_type;
}