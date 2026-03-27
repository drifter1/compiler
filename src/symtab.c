#include "../include/compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -----------------SYMBOL TABLE STRUCTURE----------------- */

symtab_entry **symbol_table = NULL;

/* ----------------SYMBOL TABLE MANAGEMENT----------------- */

void init_symbol_table() {
    int i;
    symbol_table = malloc(SIZE * sizeof(symtab_entry *));
    for (i = 0; i < SIZE; i++)
        symbol_table[i] = NULL;
}

unsigned int hash(char *key) {
    unsigned int hashval = 0;
    for (; *key != '\0'; key++)
        hashval += *key;
    hashval += key[0] % 11 + (key[0] << 3) - key[0];
    return hashval % SIZE;
}

symtab_entry *insert_symtab_entry(symtab_entry_kind kind, char *id) {
    unsigned int hashval = hash(id);

    symtab_entry *e = lookup_symtab_entry(id);

    /* variable not yet in table */
    if (e == NULL) {
        e = (symtab_entry *)malloc(sizeof(symtab_entry));
        e->kind = kind;
        strncpy(e->id, id, strlen(id));
        e->len = strlen(id);
        e->scope = cur_scope;
        e->lines = (list_node *)malloc(sizeof(list_node));
        int *p = (int *)malloc(sizeof(int));
        *p = yylineno;
        e->lines->data = (void *)p;
        e->lines->next = NULL;

        /* add to hashtable */
        e->next = symbol_table[hashval];
        symbol_table[hashval] = e;

        if (DEBUG)
            printf("Inserted %s for the first time with linenumber %d!\n", id,
                   yylineno);
    }
    /* found in table */
    else {
        /* entry in same scope or from global scope */
        if ((strcmp(e->scope->id, cur_scope->id) == 0) ||
            (e->scope->kind == GLOBAL)) {
            list_node *t = e->lines;
            while (t->next != NULL)
                t = t->next;

            /* add linenumber to reference list */
            t->next = (list_node *)malloc(sizeof(list_node));

            int *p = (int *)malloc(sizeof(int));
            *p = yylineno;
            t->next->data = (void *)p;
            t->next->next = NULL;

            if (DEBUG)
                printf("Found %s again at line %d!\n", id, yylineno);
        }
        /* new scope */
        else {
            e = (symtab_entry *)malloc(sizeof(symtab_entry));
            e->kind = kind;
            strncpy(e->id, id, strlen(id));
            e->len = strlen(id);
            e->scope = cur_scope;
            e->lines = (list_node *)malloc(sizeof(list_node));
            int *p = (int *)malloc(sizeof(int));
            *p = yylineno;
            e->lines->data = (void *)p;
            e->lines->next = NULL;

            /* add to hashtable */
            e->next = symbol_table[hashval];
            symbol_table[hashval] = e;

            if (DEBUG)
                printf("Inserted %s for a new scope with linenumber %d!\n", id,
                       yylineno);
        }
    }

    return e;
}

symtab_entry *lookup_symtab_entry(char *id) {
    unsigned int hashval = hash(id);

    symtab_entry *e = symbol_table[hashval];

    while (e != NULL) {

        // same identifier
        if (strcmp(id, e->id) == 0) {

            // same scope or global scope
            if ((strcmp(cur_scope->id, e->scope->id) == 0) ||
                (e->scope->kind == GLOBAL)) {
                break;
            }
        }

        e = e->next;
    }

    return e;
}

/* -----------------SYMBOL TABLE DUMP FILE----------------- */

void dump_symbol_table(FILE *of) {
    int i;
    fprintf(of, "------------ -------------- -------------- ------------ "
                "------------\n");
    fprintf(of, "Name         Kind           Type           Scope        Line "
                "Numbers\n");
    fprintf(of, "------------ -------------- -------------- ------------ "
                "------------\n");
    for (i = 0; i < SIZE; ++i) {
        if (symbol_table[i] != NULL) {
            symtab_entry *e = symbol_table[i];
            while (e != NULL) {
                if (strcmp(cur_scope->id, e->scope->id) != 0) {
                    enter_local_scope(e->scope->id);
                }
                fprintf(of, "%-13s", e->id);
                fprintf(of, "%-15s", symtab_entry_kind_to_string(e->kind));
                fprintf(of, "%-15s", data_type_to_string(get_data_type(e->id)));
                fprintf(of, "%-13s", e->scope->id);
                list_node *t = e->lines;
                int *lineno;
                while (t != NULL) {
                    lineno = t->data;
                    fprintf(of, "%4d ", *lineno);
                    t = t->next;
                }
                fprintf(of, "\n");
                e = e->next;
            }
        }
    }
}

/* --------------------HELPER FUNCTIONS-------------------- */

symtab_entry *insert_variable_entry(char *id, data_type d_type) {
    symtab_entry *e;

    e = insert_symtab_entry(VARIABLE_ENTRY, id);

    if (e->kind == VARIABLE_ENTRY)
        e->as.variable.d_type = d_type;

    return e;
}

symtab_entry *insert_parameter_entry(char *id, data_type d_type) {
    symtab_entry *e;

    e = insert_symtab_entry(PARAMETER_ENTRY, id);

    e->as.parameter.d_type = d_type;

    return e;
}

symtab_entry *insert_function_entry(char *id, data_type ret_type) {
    symtab_entry *e;

    e = insert_symtab_entry(FUNCTION_ENTRY, id);

    e->as.function.ret_type = ret_type;
    e->as.function.parameters = NULL;

    return e;
}

symtab_entry *set_variable_init_value(symtab_entry *entry, value val) {
    entry->as.variable.val = val;
    return entry;
}

symtab_entry *set_function_parameters(symtab_entry *entry,
                                      list_node *parameters) {
    entry->as.function.parameters = parameters;
    return entry;
}

data_type get_data_type(char *id) {
    symtab_entry *e = lookup_symtab_entry(id);

    if (e != NULL) {
        switch (e->kind) {
        case VARIABLE_ENTRY:
            return e->as.variable.d_type;
        case PARAMETER_ENTRY:
            return e->as.parameter.d_type;
        case FUNCTION_ENTRY:
            return e->as.function.ret_type;
        }
    }
    return UNDEF_TYPE;
}

char *symtab_entry_kind_to_string(symtab_entry_kind kind) {
    switch (kind) {
    case VARIABLE_ENTRY:
        return "variable";
    case PARAMETER_ENTRY:
        return "parameter";
    case FUNCTION_ENTRY:
        return "function";
    }
    return "_error";
}