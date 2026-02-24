#include "symtab.h"

#ifndef REVQUEUE_H
#define REVQUEUE_H

/* Queue of identifiers to revisit */
typedef struct revisit_queue {
    // symbol table entry
    list_t *entry;

    // name of identifier
    char *st_name;

    // type of revisit
    int revisit_type;

    // parameters of function calls
    int **par_types;
    int *num_of_pars;
    int num_of_calls;

    // assignment expression nodes
    void **nodes;
    int num_of_assigns;

    // maybe additional information to simplify the process ...

    struct revisit_queue *next;
} revisit_queue;

/* revisit types */
#define PARAM_CHECK                                                            \
    1 /* Check parameters of function call when functions gets declared */
#define ASSIGN_CHECK                                                           \
    2 /* Check assignment when function call part of the expression */

// structure
extern revisit_queue *queue;

// Revisit Queue Functions
void add_to_queue(list_t *entry, char *name, int type); // add to queue
revisit_queue *search_queue(char *name);                // search queue
revisit_queue *search_prev_queue(char *name); // search previous of element
int revisit(char *name);         // revisit entry by also removing it from queue
void revisit_dump(FILE *of);     // dump file
void remove_print();             // remove print function  rom revisit queue
void perform_remaining_checks(); // perform the remaining checks (for assignments)

#endif /* REVQUEUE_H */