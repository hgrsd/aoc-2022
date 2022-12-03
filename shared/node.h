#ifndef AOC_2022_NODE_H
#define AOC_2022_NODE_H

#include <stddef.h>

typedef struct NODE {
    void *data;
    size_t len;
    struct NODE* next;
} NODE;

NODE *empty_node();
NODE *new_node(NODE *parent, void *data, size_t len);
NODE *next_node(NODE *cur);

void destroy(NODE *head);

#endif //AOC_2022_NODE_H
