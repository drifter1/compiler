#ifndef AST_H
#define AST_H

#include "list.h"
#include "symtab.h"
#include "types.h"

/* ----------------------AST NODE KINDS--------------------- */

typedef enum {
    PROGRAM,
    DECLARATION,
    CONSTANT,
    FUNCTION,
    FUNCTION_TAIL,
    IF_STATEMENT,
    EXPRESSION_BINARY,
    EXPRESSION_UNARY,
    VARIABLE_REFERENCE,
    FUNCTION_CALL,
    ELSE_IF,
    FOR_LOOP,
    ASSIGNMENT,
    WHILE_LOOP,
    JUMP_STATEMENT,
    PRINT_STATEMENT,
    INPUT_STATEMENT,
    RETURN_STATEMENT
} ast_node_kind;

/* ------------------------AST NODES------------------------ */

typedef struct ast_node {
    ast_node_kind kind;
    int lineno;

    union {
        struct {
            list_node *declarations;
            list_node *functions;
            struct ast_node *main_function;
        } program;
        struct {
            data_type d_type;
            list_node *names;
        } declaration;
        struct {
            data_type d_type;
            value val;
        } constant;
        struct {
            symtab_entry *entry;
            struct ast_node *function_tail;
        } function;
        struct {
            list_node *declarations;
            list_node *statements;
        } function_tail;
        struct {
            struct ast_node *condition;
            list_node *if_branch;
            list_node *else_if_branches;
            list_node *else_branch;
            const char *label_if_branch;
            const char *label_else_branch;
            const char *label_end;
        } if_statement;
        struct {
            struct ast_node *left;
            operator_type op_type;
            struct ast_node *right;
            data_type d_type;
        } expression_binary;
        struct {
            struct ast_node *operand;
            operator_type op_type;
            data_type d_type;
        } expression_unary;
        struct {
            symtab_entry *entry;
        } variable_reference;
        struct {
            symtab_entry *entry;
            list_node *arguments;
        } function_call;
        struct {
            struct ast_node *condition;
            list_node *else_if_branch;
            const char *label_branch;
        } else_if;
        struct {
            struct ast_node *initialize;
            struct ast_node *condition;
            struct ast_node *increment;
            list_node *for_branch;
            const char *label_start;
            const char *label_increment;
            const char *label_end;
        } for_loop;
        struct {
            struct ast_node *variable_reference;
            struct ast_node *expression;
        } assignment;
        struct {
            struct ast_node *condition;
            list_node *while_branch;
            const char *label_start;
            const char *label_end;
        } while_loop;
        struct {
            jump_type j_type;
            const char *label_target;
        } jump_statement;
        struct {
            print_type p_type;
            union {
                const char *sval;
                struct ast_node *expression;
            } print_value;
        } print_statement;
        struct {
            struct ast_node *variable_reference;
        } input_statement;
        struct {
            data_type ret_type;
            struct ast_node *expression;
        } return_statement;
    } as;
} ast_node;

/* ---------------------AST STRUCTURE----------------------- */

extern ast_node *ast;

/* ------------------AST NODE MANAGEMENT-------------------- */

ast_node *new_ast_node(ast_node_kind kind);
ast_node *ast_program(list_node *declarations, list_node *functions,
                      ast_node *main_function);
ast_node *ast_declaration(data_type d_type, list_node *names);
ast_node *ast_constant(data_type d_type, value val);
ast_node *ast_function(symtab_entry *entry, ast_node *function_tail);
ast_node *ast_function_tail(list_node *declarations, list_node *statements);
ast_node *ast_if_statement(ast_node *condition, list_node *if_branch,
                           list_node *else_if_branches, list_node *else_branch);
ast_node *ast_expression_binary(ast_node *left, operator_type op_type,
                                ast_node *right);
ast_node *ast_expression_unary(ast_node *operand, operator_type op_type,
                               fixity_type fixity);
ast_node *ast_variable_reference(symtab_entry *entry);
ast_node *ast_function_call(symtab_entry *entry, list_node *arguments);
ast_node *ast_else_if(ast_node *condition, list_node *else_if_branch);
ast_node *ast_for_loop(ast_node *initialize, ast_node *condition,
                       ast_node *increment, list_node *for_branch);
ast_node *ast_assignment(ast_node *variable_reference, ast_node *expression);
ast_node *ast_while_loop(ast_node *condition, list_node *while_branch);
ast_node *ast_jump_statement(jump_type j_type);
ast_node *ast_print_statement(print_type p_type, const char *sval,
                              ast_node *expression);
ast_node *ast_input_statement(ast_node *variable_reference);
ast_node *ast_return_statement(data_type ret_type, ast_node *expression);
void free_ast_node(ast_node *node);
void free_ast_node_list(list_node *list_head);


/* --------------------AST NODE HELPERS--------------------- */

int ast_program_lineno(ast_node *node);
int ast_function_tail_lineno(ast_node *node);
ast_node *ast_constant_undef();
ast_node *ast_constant_init(symtab_entry *entry);
operator_type ast_expression_unary_op_type(operator_type op_type,
                                           fixity_type fixity);
char *ast_node_kind_to_string(ast_node_kind kind);

#endif /* AST_H */