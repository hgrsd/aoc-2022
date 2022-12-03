#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

void print_max(NODE *lines) {
    int max = 0;
    int cur = max;

    NODE *line = lines;
    while (line != NULL) {
        char *text = line->data;
        if (strlen(text) == 0) {
            if (cur > max) max = cur;
            cur = 0;
        } else {
            int parsed = atoi(text);
            cur += parsed;
        }
        line = next_node(line);
    }

    printf("max: %d\n", max);
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size;
    read_string("../inputs/week_1", &buffer, &buffer_size);
    NODE *lines = read_lines(buffer);
    print_max(lines);
}