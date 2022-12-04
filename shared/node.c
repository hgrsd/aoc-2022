#include <malloc.h>
#include "node.h"

NODE *next_node(NODE *cur) {
    return cur->next;
}

NODE *new_node(void* data) {
    NODE *new = malloc(sizeof(*new));
    new->next = NULL;
    new->data = data;
    return new;
}