#ifndef AOC_2022_NODE_H
#define AOC_2022_NODE_H

#include <stddef.h>

typedef struct Node {
    void *data;
    struct Node* next;
} Node;

Node *new_node(void *data);
Node *next_node(Node *cur);

#endif //AOC_2022_NODE_H
