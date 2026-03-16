#ifndef LIST_H
#define LIST_H

/* -----------------------STRUCTURES----------------------- */

typedef struct list_node {
    void *data;
    struct list_node *next;
} list_node;

/* ------------------------FUNCTIONS----------------------- */

void list_add(list_node *head, void *element);
void list_free(list_node *head);
int list_length(list_node *head);

#endif /* LIST_H */