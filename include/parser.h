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

// helper for the else_if rule
typedef struct _else_if {
    AST_Node **elsifs;
    int elseif_count;
} _else_if;

#endif /* PARSER_H */