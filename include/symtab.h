#ifndef SYMTAB_H
#define SYMTAB_H

#include "list.h"
#include "scope.h"
#include "types.h"
#include <stdio.h>

/* ---------------SYMBOL TABLE CONFIGURATION--------------- */

/* maximum size of hash table */

#ifndef SIZE
#define SIZE 211
#endif

/* ----------------SYMBOL TABLE ENTRY KINDS---------------- */

typedef enum {
    VARIABLE_ENTRY,
    PARAMETER_ENTRY,
    FUNCTION_ENTRY,
    TEMPORARY_ENTRY
} symtab_entry_kind;

/* ------------------SYMBOL TABLE ENTRIES------------------ */

typedef struct symtab_entry {
    symtab_entry_kind kind;
    const char *id;
    int len;
    scope *scope;
    list_node *lines;
    struct symtab_entry *next;

    union {
        struct {
            data_type d_type;
            struct {
                data_type d_type;
                value val;
            } init_value;
        } variable;
        struct {
            data_type d_type;
        } parameter;
        struct {
            data_type ret_type;
            list_node *parameters;
        } function;
        struct {
            data_type d_type;
        } temporary;
    } as;
} symtab_entry;

/* -----------------SYMBOL TABLE STRUCTURE----------------- */

extern symtab_entry **symbol_table;

/* ----------------SYMBOL TABLE MANAGEMENT----------------- */

void init_symbol_table();
unsigned int hash(const char *key);
symtab_entry *insert_symtab_entry(symtab_entry_kind kind, const char *id,
                                  int lineno);
symtab_entry *lookup_symtab_entry(const char *id);

/* -----------------SYMBOL TABLE DUMP FILE----------------- */

void dump_symbol_table(FILE *of);

/* --------------------HELPER FUNCTIONS-------------------- */

symtab_entry *insert_variable_entry(const char *id, data_type d_type);
symtab_entry *insert_parameter_entry(const char *id, data_type d_type);
symtab_entry *insert_function_entry(const char *id, data_type ret_type);
symtab_entry *insert_temporary_entry(const char *id, int lineno,
                                     data_type d_type);
symtab_entry *set_variable_init_value(symtab_entry *entry, data_type d_type,
                                      value val);
symtab_entry *set_function_parameters(symtab_entry *entry,
                                      list_node *parameters);
data_type get_data_type(const char *id);
char *symtab_entry_kind_to_string(symtab_entry_kind kind);
int get_first_lineno(symtab_entry *entry);

#endif /* SYMTAB_H */