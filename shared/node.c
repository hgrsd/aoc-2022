#include <malloc.h>
#include "node.h"

Node *next_node(Node *cur) {
    return cur->next;
}

Node *new_node(void* data) {
    Node *new = malloc(sizeof(*new));
    new->next = NULL;
    new->data = data;
    return new;
}