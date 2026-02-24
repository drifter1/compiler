#include "../include/revqueue.h"
#include "../include/semantics.h"

#include <stdlib.h>
#include <string.h>

// structure
revisit_queue *queue = NULL;

// Revisit Queue Functions

void add_to_queue(list_t *entry, char *name, int type) { /* add to queue */
    revisit_queue *q;

    /* queue is empty */
    if (queue == NULL) {
        /* set up entry */
        q = (revisit_queue *)malloc(sizeof(revisit_queue));
        q->entry = entry;
        q->st_name = name;
        q->revisit_type = type;
        q->next = NULL;

        /* additional info */
        if (type == PARAM_CHECK) {
            q->num_of_calls = 0;
        } else if (type == ASSIGN_CHECK) {
            q->num_of_assigns = 0;
        }

        /* q "becomes" the queue */
        queue = q;
    }
    /* queue not empty */
    else {
        /* find last element */
        q = queue;
        while (q->next != NULL)
            q = q->next;

        /* add element to the end */
        q->next = (revisit_queue *)malloc(sizeof(revisit_queue));
        q->next->entry = entry;
        q->next->st_name = name;
        q->next->revisit_type = type;
        q->next->next = NULL;

        /* additional info */
        if (type == PARAM_CHECK) {
            q->next->num_of_calls = 0;
        } else if (type == ASSIGN_CHECK) {
            q->next->num_of_assigns = 0;
        }
    }
}

revisit_queue *search_queue(char *name) { /* search queue */
    revisit_queue *q;

    /* search for the entry */
    q = queue;
    while ((q != NULL) && (strcmp(q->st_name, name) != 0))
        q = q->next;

    return q;
}

revisit_queue *search_prev_queue(char *name) {
    revisit_queue *q;

    /* queue is empty */
    if (queue == NULL) {
        return NULL;
    }

    /* special case - first entry */
    if (strcmp(queue->st_name, name) == 0) {
        return NULL;
    }

    /* search for the entry */
    q = queue;
    while ((q != NULL) && (strcmp(q->next->st_name, name) != 0))
        q = q->next;

    return q;
}

int revisit(char *name) { /* revisit entry by also removing it from queue */
    int i, type1, type2;

    revisit_queue *q = search_queue(name);
    revisit_queue *q2;

    if (q == NULL) {
        return -1; // no entry
    }

    /* revisit entry depending on the type */
    switch (q->revisit_type) {
    case PARAM_CHECK:
        /* run parameter check */
        if (!func_param_check(name, q->num_of_calls, q->par_types,
                              q->num_of_pars)) {
            printf("Successful Parameter Check of %s\n", name);
        }

        /* remove entry by making it point to it's next */
        q2 = search_prev_queue(name);
        if (q2 == NULL) { /* special case: first entry */
            queue = queue->next;
        } else {
            q2->next = q2->next->next;
        }

        break;
    case ASSIGN_CHECK:

        /* run assignment check for each assignment */
        type1 = get_type(q->entry->st_name);
        for (i = 0; i < q->num_of_assigns; i++) {
            type2 = expression_data_type(q->nodes[i]);

            /* perform assignment check */
            get_result_type(type1, /*  variable datatype  */
                            type2, /* expression datatype */
                            NONE /* checking compatibility only (no operator) */
            );
        }

        /* remove entry by making it point to it's next */
        q2 = search_prev_queue(name);
        if (q2 == NULL) { /* special case: first entry */
            queue = queue->next;
        } else {
            q2->next = q2->next->next;
        }

        break;
        /* ... */
    }

    return 0; // success
}

void revisit_dump(FILE *of) {
    int i;
    revisit_queue *q;
    q = queue;

    fprintf(of, "------------ -------------\n");
    fprintf(of, "Identifier   Revisit Type\n");
    fprintf(of, "------------ -------------\n");
    while (q != NULL) {
        fprintf(of, "%-13s", q->st_name);
        if (q->revisit_type == PARAM_CHECK) {
            fprintf(of, "%s", "Parameter Check ");
            fprintf(of, "for %d function calls", q->num_of_calls);
        } else if (q->revisit_type == ASSIGN_CHECK) {
            fprintf(of, "%s", "Assignment Check ");
            fprintf(of, "for %d assignments", q->num_of_assigns);
        }
        // more later on
        fprintf(of, "\n");
        q = q->next;
    }
}

void remove_print() { // remove print function from revisit queue
    revisit_queue *q = search_prev_queue("print");
    if (q == NULL) {         /* special case: first entry */
        if (queue != NULL) { /* check if queue not empty */
            queue = queue->next;
        }
    } else {
        q->next = q->next->next;
    }
}

void perform_remaining_checks() { // perform the remaining checks (for
                                  // assignments)
    if (queue != NULL) {
        revisit_queue *cur;
        cur = queue;
        while (cur != NULL) {
            if (cur->revisit_type == ASSIGN_CHECK) {
                revisit(cur->st_name);
            }
            cur = cur->next;
        }
    }

    /* if still not empty -> Warning */
    if (queue != NULL) {
        printf(
            "Warning: Something has not been checked in the revisit queue!\n");
    }
}