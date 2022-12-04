//
// Created by daniel on 03/12/22.
//

#ifndef AOC_2022_LIST_H
#define AOC_2022_LIST_H

#include "node.h"

typedef struct List{
    NODE *head;
    NODE *tail;
    NODE *cur_iter;
} List;

List *new_list(void);
List *map(List *list, void *(fn)(void * elem));

int sum(List *list);

void rewind_list(List *list);
void destroy(List *list);
void append(List *list, void *data);
void *get_next(List *list);

#endif //AOC_2022_LIST_H
