#include "../include/compiler.h"
#include <stdlib.h>
#include <string.h>

/* ----------------------CURRENT SCOPE--------------------- */

scope *cur_scope = NULL;

/* --------------------SCOPE MANAGEMENT-------------------- */

void init_scope() { cur_scope = new_global_scope(); }

void hide_scope(char *id) {
    if (DEBUG)
        printf("Hiding scope \'%s\'\n", id);

    cur_scope->visibility = HIDDEN;
    cur_scope = cur_scope->parent;
}

void hide_current_scope() { hide_scope(cur_scope->id); }

scope *new_scope(scope_kind kind, char *id) {
    scope *s = malloc(sizeof(scope));
    s->kind = kind;
    s->id = id;
    s->visibility = VISIBLE;
    s->parent = cur_scope;
    return s;
}

scope *new_global_scope() { return new_scope(GLOBAL, "_GLOBAL"); }

scope *new_local_scope(char *id) { return new_scope((LOCAL), id); }

void enter_local_scope(char *id) {
    if (DEBUG)
        printf("Entering scope \'%s\'\n", id);
    cur_scope = new_local_scope(id);
}
