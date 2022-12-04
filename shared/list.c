#include <malloc.h>
#include "list.h"

LIST *new_list(void) {
   LIST *new = malloc(sizeof(*new));
   new->head = NULL;
   new->tail = NULL;
   new->cur_iter = NULL;
}

LIST *map(LIST *list, void *(fn)(void * elem)) {
    LIST *mapped = new_list();
    void *elem;
    while ((elem = get_next(list)) != NULL) {
        void *m = fn(elem);
        append(mapped, m);
    }
    return mapped;
}

void destroy(LIST *list) {
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

void append(LIST *list, void *data) {
    NODE *new = new_node(data);

    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    }
}

void rewind_list(LIST *list) {
    list->cur_iter = NULL;
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
