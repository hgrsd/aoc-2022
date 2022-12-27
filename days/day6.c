#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "charset.h"

int has_unique_chars(CharSet s, const char *c, size_t len) {
    for (int i = 0; i < len; i++) {
        if (has(c + i, s)) {
            return 0;
        }
        add(c + i, s);
    }
    return 1;
}

int index_after_n_uniques(CharSet s, int n, const char *buf) {
    for (int i = 0; i < strlen(buf) - n; i++) {
        if (has_unique_chars(s, buf + i, n)) {
            return i + n;
        }
        clear(s);
    }

    return -1;
}

int main(void) {
    char *buf;
    size_t sz;

    read_string("../inputs/day_6", &buf, &sz);

    CharSet s = new_charset();
    int part1 = index_after_n_uniques(s, 4, buf);
    printf("day 6, part 1: %d\n", part1);
    clear(s);

    int part2 = index_after_n_uniques(s, 14, buf);
    printf("day 6, part 2: %d\n", part2);

    free(s);
    free(buf);
}