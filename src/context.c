#include "../include/compiler.h"
#include <stdlib.h>

/* ----------------------CURRENT CONTEXT--------------------- */

context *cur_context;

/* --------------------CONTEXT MANAGEMENT-------------------- */

void init_context() { cur_context = new_context(NULL); }

void hide_current_context() {
#if DEBUG
    printf("Hiding context with kind \'%s\'\n",
           context_kind_to_string(cur_context->kind));
#endif

    context *temp = cur_context;
    cur_context = cur_context->parent;
    free(temp);
}

context *new_context(ast_node *node) {

    context *c = (context *)malloc(sizeof(context));

    c->parent = cur_context;

    if (node == NULL) {
        c->kind = NO_CONTEXT;
    } else {
        switch (node->kind) {
        case FOR_LOOP:
            c->kind = IN_FOR_LOOP;
            break;
        case WHILE_LOOP:
            c->kind = IN_WHILE_LOOP;
            break;
        default:
            c->kind = NO_CONTEXT;
        }
    }

    c->node = node;

    return c;
}

void enter_new_context(ast_node *node) {
#if DEBUG
    printf("Entering context with node of kind \'%s\'\n",
           ast_node_kind_to_string(node->kind));
#endif

    cur_context = new_context(node);
}

/* --------------------HELPER FUNCTIONS-------------------- */

const char *get_current_break_target() {
    switch (cur_context->kind) {
    case NO_CONTEXT:
        return NULL;
    case IN_FOR_LOOP:
        return cur_context->node->as.for_loop.label_end;
    case IN_WHILE_LOOP:
        return cur_context->node->as.while_loop.label_end;
    }
    return NULL;
}

const char *get_current_continue_target() {
    switch (cur_context->kind) {
    case NO_CONTEXT:
        return NULL;
    case IN_FOR_LOOP:
        return cur_context->node->as.for_loop.label_increment;
    case IN_WHILE_LOOP:
        return cur_context->node->as.while_loop.label_start;
    }
    return NULL;
}

int in_context_of_kind(context *c, context_kind kind) {
    if (c == NULL)
        return 0;
    if (c->kind == kind)
        return 1;
    return in_context_of_kind(c->parent, kind);
}

char *context_kind_to_string(context_kind kind) {
    switch (kind) {
    case NO_CONTEXT:
        return "no_context";
    case IN_FOR_LOOP:
        return "in_for_loop";
    case IN_WHILE_LOOP:
        return "in_while_loop";
    }
    return "_error";
}