#ifndef AOC_2022_LIST_H
#define AOC_2022_LIST_H
#define iter_list(list, elem, type) for(type elem = get_next(list); elem != NULL; elem = get_next(list))


#include "node.h"

typedef struct List {
    Node *head;
    Node *tail;
    Node *cur_iter;
    size_t len;
} List;

List *new_list(void);

List *map(List *list, void *(fn)(void *elem));

int sum(List *list);

void rewind_list(List *list);

void destroy(List *list);

void push_back(List *list, void *data);

void push(List *list, void *data);

void *pop(List *list);

int has_next(List *list);

void *get_next(List *list);

void reverse(List *list);

#endif //AOC_2022_LIST_H
