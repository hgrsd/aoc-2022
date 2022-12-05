#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

void *parse(void *input) {
    int *parsed = malloc(sizeof(*parsed));

    char *i = input;
    if (strlen(i) == 0) {
        *parsed = -1;
    } else {
        *parsed = atoi(i);
    }
    return parsed;
}

void part1(List *numbers) {
    int richest_elf = 0;
    int current_elf = richest_elf;

    iter_list(numbers, number, int*) {
        if (*number == -1) {
            if (current_elf > richest_elf) richest_elf = current_elf;
            current_elf = 0;
        } else {
            current_elf += *number;
        }
    }

    rewind_list(numbers);

    printf("richest_elf: %d\n", richest_elf);


int cmp(const void *left, const void *right) {
    int *l = (int *) left;
    int *r = (int *) right;
    if (*l < *r) {
        return -1;
    }

    if (*r < *l) {
        return 1;
    }

    return 0;
}

void maybe_swap(int top3[3], int cur) {
    qsort(top3, 3, sizeof(int), cmp);
    for (int i = 0; i < 3; i++) {
        if (cur > top3[i]) {
            top3[i] = cur;
            break;
        }
    }
}

void part2(List *numbers) {
    int top3[3] = {0, 0, 0};

    int current_elf = 0;
    for (int *number = get_next(numbers); number != NULL; number = get_next(numbers)) {
        if (*number == -1) {
            maybe_swap(top3, current_elf);
            current_elf = 0;
        } else {
            current_elf += *number;
        }
    }

    printf("max sum: %d\n", top3[0] + top3[1] + top3[2]);
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size;

    read_string("../inputs/day_1", &buffer, &buffer_size);

    List *lines = split_by('\n', buffer);
    free(buffer);

    List *parsed = map(lines, parse);
    destroy(lines);

    part1(parsed);
    part2(parsed);
}