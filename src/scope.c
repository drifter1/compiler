#include "../include/scope.h"
#include "../include/debug.h"
#include <stdlib.h>

/* ----------------------CURRENT SCOPE--------------------- */

scope *cur_scope = NULL;

/* --------------------SCOPE MANAGEMENT-------------------- */

void init_scope() { cur_scope = new_global_scope(); }

void hide_current_scope() {

#if SCOPE_DEBUG
    printf("Hiding scope \'%s\'\n", cur_scope->id);
#endif

    cur_scope->visibility = HIDDEN;
    cur_scope = cur_scope->parent;
}

scope *new_scope(scope_kind kind, const char *id) {
    scope *s = malloc(sizeof(scope));
    s->kind = kind;
    s->id = id;
    s->visibility = VISIBLE;
    s->parent = cur_scope;
    return s;
}

scope *new_global_scope() { return new_scope(GLOBAL, "_GLOBAL"); }

scope *new_local_scope(const char *id) { return new_scope((LOCAL), id); }

void enter_local_scope(const char *id) {

#if SCOPE_DEBUG
    printf("Entering scope \'%s\'\n", id);
#endif

    cur_scope = new_local_scope(id);
}

/* --------------------HELPER FUNCTIONS-------------------- */

char *scope_kind_to_string(scope_kind kind) {
    switch (kind) {
    case GLOBAL:
        return "global";
    case LOCAL:
        return "local";
    }
    return "_error";
}

char *visibility_kind_to_string(visibility_kind kind) {
    switch (kind) {
    case VISIBLE:
        return "visible";
    case HIDDEN:
        return "hidden";
    }
    return "_error";
}
