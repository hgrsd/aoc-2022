#include <malloc.h>
#include <string.h>
#include "common.h"

int has_unique_chars(const char *c, size_t len) {
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (c[i] == c[j]) {
                return 0;
            }
        }
    }

    return 1;
}

int index_after_n_uniques(int n, const char *buf) {
    for (int i = 0; i < strlen(buf) - n; i++) {
        if (has_unique_chars(buf + i, n)) {
           return i + n;
        }
    }

    return -1;
}

int main(void) {
    char *buf;
    size_t sz;

    read_string("../inputs/day_6", &buf, &sz);

    int part1 = index_after_n_uniques(4, buf);
    printf("day 6, part 1: %d\n", part1);

    int part2 = index_after_n_uniques(14, buf);
    printf("day 6, part 2: %d\n", part2);

    free(buf);
}