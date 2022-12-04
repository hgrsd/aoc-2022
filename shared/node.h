#ifndef AOC_2022_NODE_H
#define AOC_2022_NODE_H

#include <stddef.h>

typedef struct NODE {
    void *data;
    struct NODE* next;
} NODE;

NODE *new_node(void *data);
NODE *next_node(NODE *cur);

#endif //AOC_2022_NODE_H
