#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

void print_max(char *buf) {
    int max, cur = 0;
    char *start, *end;

    start = end = buf;

    while ((end = strchr(start, '\n')) != NULL) {
        if (*start == '\n') {
            if (cur > max) max = cur;
            cur = 0;
        } else {
            char temp[32];
            snprintf(temp, 32, "%.*s", (int) (end - start), start);
            int parsed = atoi(temp);
            cur += parsed;
        }
        start = end + 1;
    }

    printf("max: %d\n", max);
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size;

    read_string("../inputs/week_1", &buffer, &buffer_size);
    print_max(buffer);
}