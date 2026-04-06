#ifndef CONTEXT_H
#define CONTEXT_H

#include "ast.h"

/* -----------------------CONTEXT KINDS---------------------- */

typedef enum { NO_CONTEXT, IN_FOR_LOOP, IN_WHILE_LOOP } context_kind;

/* ---------------------SCOPE STRUCTURE-------------------- */

typedef struct context {
    struct context *parent;
    context_kind kind;
    ast_node *node;
} context;

/* ----------------------CURRENT CONTEXT--------------------- */

extern context *cur_context;

/* --------------------CONTEXT MANAGEMENT-------------------- */

void init_context();
void hide_current_context();
context *new_context(ast_node *node);
void enter_new_context(ast_node *node);

/* --------------------HELPER FUNCTIONS-------------------- */

const char *get_current_break_target();
const char *get_current_continue_target();
int in_context_of_kind(context *c, context_kind kind);
char *context_kind_to_string(context_kind kind);

#endif /* CONTEXT_H */