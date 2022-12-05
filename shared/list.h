#ifndef AOC_2022_LIST_H
#define AOC_2022_LIST_H
#define iter_list(list, elem, type) for(type elem = get_next(list); elem != NULL; elem = get_next(list))



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
int has_next(List *list);
void *get_next(List *list);

#endif //AOC_2022_LIST_H
