//
// Created by daniel on 03/12/22.
//

#ifndef AOC_2022_LIST_H
#define AOC_2022_LIST_H

#include "node.h"

typedef struct LIST {
    NODE *head;
    NODE *tail;
    NODE *cur_iter;
} LIST;

LIST *new_list(void);
void append(LIST *list, void *data, size_t data_len);
void *get_next(LIST *list);

#endif //AOC_2022_LIST_H
