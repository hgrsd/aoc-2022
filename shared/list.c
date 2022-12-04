#include <malloc.h>
#include "list.h"

LIST *new_list(void) {
   LIST *new = malloc(sizeof(*new));
   new->head = NULL;
   new->tail = NULL;
   new->cur_iter = NULL;
}

void append(LIST *list, void *data, size_t data_len) {
    NODE *new = empty_node();
    new->next = NULL;
    new->data = data;
    new->len = data_len;

    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    }
}

void *get_next(LIST *list) {
    if (list->cur_iter == NULL && list->head) {
        list->cur_iter = list->head;
        return list->head->data;
    }

    if (list->cur_iter == NULL || list->cur_iter->next == NULL) {
        return NULL;
    }

    void *val = list->cur_iter->data;
    list->cur_iter = list->cur_iter->next;
    return val;
}
