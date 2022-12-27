#include <stdlib.h>
#include <memory.h>
#include "charset.h"

#define START_OFFSET 65
#define LEN 58

static int as_int(const char *c) {
    return *c - START_OFFSET;
}

CharSet new_charset(void) {
    int *set = malloc(sizeof(*set) * LEN);
    memset(set, 0, LEN);
    return set;
}

void clear(CharSet s) {
    memset(s, 0, LEN);
}

void add(const char *c, CharSet s) {
    int i = as_int(c);
    s[i] = 1;
}

int has(const char *c, CharSet s) {
    int i = as_int(c);
    return s[i] == 1;
}
