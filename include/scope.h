#ifndef SCOPE_H
#define SCOPE_H

/* -----------------------SCOPE KINDS---------------------- */

typedef enum { GLOBAL, LOCAL } scope_kind;

/* --------------------VISIBILITY KINDS-------------------- */

typedef enum { VISIBLE, HIDDEN } visibility_kind;

/* ---------------------SCOPE STRUCTURE-------------------- */

typedef struct scope {
    struct scope *parent;
    scope_kind kind;
    const char *id;
    visibility_kind visibility;
} scope;

/* ----------------------CURRENT SCOPE--------------------- */

extern scope *cur_scope;

/* --------------------SCOPE MANAGEMENT-------------------- */

void init_scope();
void hide_current_scope();
scope *new_scope(scope_kind kind, const char *id);
scope *new_global_scope();
scope *new_local_scope(const char *id);
void enter_local_scope(const char *id);

/* --------------------HELPER FUNCTIONS-------------------- */

char *scope_kind_to_string(scope_kind kind);
char *visibility_kind_to_string(visibility_kind kind);

#endif /* SCOPE_H */