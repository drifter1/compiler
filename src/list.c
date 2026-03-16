#include "../include/list.h"
#include <stdlib.h>

void list_add(list_node *head, void *element) {
    list_node *current;

    current = head;
    while (current != NULL) {
        current = current->next;
    }

    current = (list_node *)malloc(sizeof(list_node));
    current->data = element;
    current->next = NULL;
}

void list_free(list_node *head) {
    list_node *current;

    while (head != NULL) {
        current = head;
        head = head->next;
        free(current);
    }
}

int list_length(list_node *head) {
    int length = 0;
    list_node *current;

    current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }

    return length;
}