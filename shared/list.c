#include <stdlib.h>
#include <assert.h>
#include "list.h"

Node *next_node(Node *cur) {
    return cur->next;
}

Node *new_node(void *data) {
    Node *new = malloc(sizeof(*new));
    new->next = NULL;
    new->data = data;
    return new;
}


List *new_list(void) {
    List *new = malloc(sizeof(*new));
    new->head = NULL;
    new->tail = NULL;
    new->cur_iter = NULL;
    new->len = 0;
    return new;
}

List *map(List *list, void *(fn)(void *elem)) {
    List *mapped = new_list();
    void *elem;
    while ((elem = get_next(list)) != NULL) {
        void *m = fn(elem);
        push_back(mapped, m);
    }
    rewind_list(list);
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

void destroy_list(List *list, int should_free_data) {
    while (list->head != NULL) {
        Node *next = next_node(list->head);
        if (list->head->data != NULL && should_free_data) {
            free(list->head->data);
        }
        free(list->head);
        list->head = next;
    }
    free(list);
}

void push_back(List *list, void *data) {
    assert(list->cur_iter == NULL);

    Node *new = new_node(data);

    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    }

    list->len++;
}

void push(List *list, void *data) {
    assert(list->cur_iter == NULL);

    Node *new = new_node(data);
    if (list->head) {
        new->next = list->head;
    }

    list->head = new;
    list->len++;
}

void *pop(List *list) {
    assert(list->cur_iter == NULL);

    Node *n = list->head;
    if (!n) {
        return NULL;
    }

    list->head = n->next;
    void *data = n->data;
    free(n);
    return data;
}

void rewind_list(List *list) {
    list->cur_iter = NULL;
}

int has_next(List *list) {
    if (list->cur_iter == NULL && list->head) {
        return 1;
    }

    if (list->cur_iter && list->cur_iter->next) {
        return 1;
    }

    return 0;
}

Node *get_next_node(List *list) {
    if (list->cur_iter == NULL && list->head) {
        list->cur_iter = list->head;
        return list->head;
    }

    if (list->cur_iter == NULL || list->cur_iter->next == NULL) {
        return NULL;
    }

    Node *next = list->cur_iter->next;
    list->cur_iter = next;
    return next;
}

void *get_next(List *list) {
    Node *next = get_next_node(list);
    return next ? next->data : NULL;
}

void reverse(List *list) {
    Node *cur = list->head;
    list->tail = list->head;
    Node *prev = NULL;
    Node *next = NULL;

    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    list->head = prev;
}
