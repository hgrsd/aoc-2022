#include <malloc.h>
#include "list.h"

List *new_list(void) {
   List *new = malloc(sizeof(*new));
   new->head = NULL;
   new->tail = NULL;
   new->cur_iter = NULL;
}

List *map(List *list, void *(fn)(void * elem)) {
    List *mapped = new_list();
    void *elem;
    while ((elem = get_next(list)) != NULL) {
        void *m = fn(elem);
        append(mapped, m);
    }
    return mapped;
}

int sum(List *list) {
    int total = 0;
    void *elem;
    while ((elem = get_next(list)) != NULL) {
        total += *(int *) elem;
    }
    rewind_list(list);
    return total;
}

void destroy(List *list) {
    while(list->head != NULL) {
        NODE *next = next_node(list->head);
        if(list->head->data != NULL) {
            free(list->head->data);
        }
        free(list->head);
        list->head = next;
    }
    free(list);
}

void append(List *list, void *data) {
    NODE *new = new_node(data);

    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    }
}

void rewind_list(List *list) {
    list->cur_iter = NULL;
}

void *get_next(List *list) {
    if (list->cur_iter == NULL && list->head) {
        list->cur_iter = list->head;
        return list->head->data;
    }

    if (list->cur_iter == NULL || list->cur_iter->next == NULL) {
        return NULL;
    }

    NODE *next = list->cur_iter->next;
    list->cur_iter = next;
    return next->data;
}
