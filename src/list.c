#include "../include/list.h"
#include <stdlib.h>

list_node *list_add(list_node *head, void *element) {

    if (head == NULL) {
        head = (list_node *)malloc(sizeof(list_node));
        head->data = (void *)element;
        head->next = NULL;
        return head;
    }

    list_node *current;

    current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = (list_node *)malloc(sizeof(list_node));
    current->next->data = (void *)element;
    current->next->next = NULL;

    return head;
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