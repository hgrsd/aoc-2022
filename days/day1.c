#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

void *parse(void* input) {
    int *parsed = malloc(sizeof(*parsed));

    char *i = input;
    if (strlen(i) == 0) {
        *parsed = -1;
    } else {
        *parsed = atoi(i);
    }
    return parsed;
}

void print_max(LIST *numbers) {
    int max = 0;
    int cur = max;

    int *number;
    while ((number = get_next(numbers)) != NULL) {
        if (*number == -1) {
            if (cur > max) max = cur;
            cur = 0;
        } else {
            cur += *number;
        }
    }

    printf("max: %d\n", max);
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size;
    read_string("../inputs/day_1", &buffer, &buffer_size);
    LIST *parsed_lines = map(to_lines(buffer), parse);
    print_max(parsed_lines);
}