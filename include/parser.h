#include "ast.h"

#ifndef PARSER_H
#define PARSER_H

// helper for the names rule
typedef struct _names {
    list_t **names;
    int names_count;
} _names;

// helper for the values rule
typedef struct _values {
    Value *vals;
    int val_count;
} _values;

// helper for the function_head rule
typedef struct _function_head {
    AST_Node *ret_type;
    list_t *entry;
    AST_Node *decl_params;
} _function_head;

// helper for the function_tail rule
typedef struct _function_tail {
    AST_Node *declarations;
    AST_Node *statements;
    AST_Node *return_node;
} _function_tail;

#endif /* PARSER_H */