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

NODE *new_node(NODE *parent, void *data, size_t len) {
    NODE *new = empty_node();
    new->len = len;
    new->data = data;
    if (parent != NULL) {
        parent->next = new;
    }
    return new;
}
