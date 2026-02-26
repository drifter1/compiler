#include "../include/ast.h"
#include "../include/revqueue.h"
#include "../include/semantics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* current scope */
int cur_scope = 0;

/* flag variable for declaring */
int declare = 0; // 1: declaring variable, 0: not

/* flag variable for function declaring */
int function_decl = 0; // 1: declaring function, 0: not

// structure
list_t **hash_table = NULL;

// Symbol Table Functions

void init_hash_table() {
    int i;
    hash_table = malloc(SIZE * sizeof(list_t *));
    for (i = 0; i < SIZE; i++)
        hash_table[i] = NULL;
}

unsigned int hash(char *key) {
    unsigned int hashval = 0;
    for (; *key != '\0'; key++)
        hashval += *key;
    hashval += key[0] % 11 + (key[0] << 3) - key[0];
    return hashval % SIZE;
}

void insert(char *name, int len, int type, int lineno) {
    unsigned int hashval = hash(name);
    list_t *l = hash_table[hashval];

    while ((l != NULL) && (strcmp(name, l->st_name) != 0))
        l = l->next;

    /* variable not yet in table */
    if (l == NULL) {
        /* check if we are declaring */
        if (declare == 1) {
            /* set up entry */
            l = (list_t *)malloc(sizeof(list_t));
            strncpy(l->st_name, name, len);
            l->st_size = len;
            l->st_type = type;
            l->scope = cur_scope;
            l->lines = (RefList *)malloc(sizeof(RefList));
            l->lines->lineno = lineno;
            l->lines->next = NULL;

            /* add to hashtable */
            l->next = hash_table[hashval];
            hash_table[hashval] = l;
            // printf("Inserted %s for the first time with linenumber %d!\n",
            // name, lineno);
        } else {
            /* add it to check it again later */
            l = (list_t *)malloc(sizeof(list_t));
            strncpy(l->st_name, name, len);
            l->st_size = len;
            l->st_type = type;
            l->scope = cur_scope;
            l->lines = (RefList *)malloc(sizeof(RefList));
            l->lines->lineno = lineno;
            l->lines->next = NULL;
            l->next = hash_table[hashval];
            hash_table[hashval] = l;
            // printf("Inserted %s at line %d to check it again later!\n", name,
            // lineno);

            /* Adding identifier to the revisit queue */
            add_to_queue(l, l->st_name, PARAM_CHECK);
        }
    }
    /* found in table */
    else {
        // just add line number
        if (declare == 0) {
            /* find last reference */
            RefList *t = l->lines;
            while (t->next != NULL)
                t = t->next;

            /* add linenumber to reference list */
            t->next = (RefList *)malloc(sizeof(RefList));
            t->next->lineno = lineno;
            t->next->next = NULL;
            // printf("Found %s again at line %d!\n", name, lineno);
        }
        /* new entry */
        else {
            /* same scope - multiple declaration error! */
            if (l->scope == cur_scope) {
                fprintf(stderr,
                        "A multiple declaration of variable %s at line %d\n",
                        name, lineno);
                exit(1);
            }
            /* other scope - but function declaration */
            else if (function_decl == 1) {
                /* find last reference */
                RefList *t = l->lines;
                while (t->next != NULL)
                    t = t->next;

                /* add linenumber to reference list */
                t->next = (RefList *)malloc(sizeof(RefList));
                t->next->lineno = lineno;
                t->next->next = NULL;
            }
            /* other scope - create new entry */
            else {
                /* set up entry */
                l = (list_t *)malloc(sizeof(list_t));
                strncpy(l->st_name, name, len);
                l->st_size = len;
                l->st_type = type;
                l->scope = cur_scope;
                l->lines = (RefList *)malloc(sizeof(RefList));
                l->lines->lineno = lineno;
                l->lines->next = NULL;

                /* add to hashtable */
                l->next = hash_table[hashval];
                hash_table[hashval] = l;
                // printf("Inserted %s for a new scope with linenumber %d!\n",
                // name, lineno);
            }
        }
    }
}

list_t *lookup(char *name) { /* return symbol if found or NULL if not found */
    unsigned int hashval = hash(name);
    list_t *l = hash_table[hashval];
    while ((l != NULL) && (strcmp(name, l->st_name) != 0))
        l = l->next;
    return l;
}

// Type Functions

void set_type(char *name, int st_type,
              int inf_type) { // set the type of an entry (declaration)
    /* lookup entry */
    list_t *l = lookup(name);

    /* set as "main" type */
    l->st_type = st_type;

    /* if array, pointer or function */
    if (inf_type != UNDEF) {
        l->inf_type = inf_type;
    }
}

int get_type(char *name) { // get the type of an entry
    /* lookup entry */
    list_t *l = lookup(name);

    /* if "simple" type */
    if (l->st_type == INT_TYPE || l->st_type == REAL_TYPE ||
        l->st_type == CHAR_TYPE) {
        return l->st_type;
    }
    /* if array, pointer or function */
    else {
        return l->inf_type;
    }
}

// Scope Management Functions

void hide_scope() { /* hide the current scope */
    list_t *l;
    int i;
    // printf("Hiding scope \'%d\':\n", cur_scope);
    /* for all the lists */
    for (i = 0; i < SIZE; i++) {
        if (hash_table[i] != NULL) {
            l = hash_table[i];
            /* Find the first item that is from another scope */
            while (l != NULL && l->scope == cur_scope) {
                // printf("Hiding %s..\n", l->st_name);
                l = l->next;
            }
            /* Set the list equal to that item */
            hash_table[i] = l;
        }
    }
    cur_scope--;
}

void incr_scope() { /* go to next scope */ cur_scope++; }

// Function Declaration and Parameters

Param def_param(int par_type, char *param_name,
                int passing) { // define parameter
    Param param;               /* Parameter struct */

    /* set the information */
    param.par_type = par_type;
    strcpy(param.param_name, param_name);
    param.passing = passing;

    /* return the structure */
    return param;
}

int func_declare(char *name, int ret_type, int num_of_pars,
                 Param *parameters) { // declare function
    /* lookup entry */
    list_t *l = lookup(name);

    if (l != NULL) {
        /* if type is not defined yet */
        if (l->st_type == UNDEF) {
            /* entry is of function type */
            l->st_type = FUNCTION_TYPE;

            /* return type is ret_type */
            l->inf_type = ret_type;

            /* parameter stuff */
            l->num_of_pars = num_of_pars;
            l->parameters = parameters;

            return 0; /* success */
        }
        /* already declared error */
        else {
            fprintf(stderr, "Function %s already declared!\n", name);
            exit(1);
        }
    }
}

int func_param_check(char *name, int num_of_calls, int **par_types,
                     int *num_of_pars) { // check parameters
    int i, j, type_1, type_2;

    /* lookup entry */
    list_t *l = lookup(name);

    /* for all function calls */
    for (i = 0; i < num_of_calls; i++) {
        /* check number of parameters */
        if (l->num_of_pars != num_of_pars[i]) {
            fprintf(stderr,
                    "Function call of %s has wrong num of parameters!\n", name);
            exit(1);
        }
        /* check if parameters are compatible */
        for (j = 0; j < num_of_pars[i]; j++) {
            /* type of parameter in function declaration */
            type_1 = l->parameters[j].par_type;

            /* type of parameter in function call*/
            type_2 = par_types[i][j];

            /* check compatibility for function call */
            get_result_type(type_1, type_2, NONE);
            /* error occurs automatically in the function */
        }
    }

    return 0; /* success */
}