#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

void print_max(LIST *lines) {
    int max = 0;
    int cur = max;

    char *line;
    while ((line = get_next(lines)) != NULL) {
        if (strlen(line) == 0) {
            if (cur > max) max = cur;
            cur = 0;
        } else {
            int parsed = atoi(line);
            cur += parsed;
        }
    }

    printf("max: %d\n", max);
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size;
    read_string("../inputs/week_1", &buffer, &buffer_size);
    LIST *lines = to_lines(buffer);
    print_max(lines);
}