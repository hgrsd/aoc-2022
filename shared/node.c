#include <malloc.h>
#include "node.h"

NODE *next_node(NODE *cur) {
    return cur->next;
}

NODE *empty_node(void) {
    NODE *new = malloc(sizeof(*new));
    new->next = NULL;
    new->len = 0;
    new->data = NULL;
    return new;
}