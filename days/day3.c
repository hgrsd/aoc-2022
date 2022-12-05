#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <ctype.h>
#include "common.h"

int get_priority(char character) {
    int upper = isupper(character);
    int uppercased = toupper(character);
    int uppercase_value = uppercased - 64; // make sure 'A' is valued at 1.
    return upper ? uppercase_value + 26 : uppercase_value;
}

void *duplicate_priority(void *line) {
    int *p = malloc(sizeof(*p));
    char *l = line;

    int len = (int) strlen(l);
    int boundary = len / 2;

    for (int i = 0; i < boundary; i++) {
        char c = l[i];
        for (int j = boundary; j < len; j++) {
            if (l[j] == c) {
                *p = get_priority(c);
                return p;
            }
        }
    }

    assert(!"Invariant breached: should be a duplicate");
}

void part_1(List *lines) {
    int total = sum(map(lines, duplicate_priority));
    rewind_list(lines);
    printf("part 1: %d\n", total);
}

char find_badge(char *backpack_one, char *backpack_two, char* backpack_three) {
    for(int i = 0; i < strlen(backpack_one); i++) {
        char target = backpack_one[i];

        for (int j = 0; j < strlen(backpack_two); j++) {
            char possible_first_match = backpack_two[j];

            if (target == possible_first_match) {
                for (int k = 0; k < strlen(backpack_three); k++) {
                    char possible_second_match = backpack_three[k];

                    if (target == possible_second_match) {
                        return target;
                    }
                }
            }
        }
    }

    assert(!"Invariant breached: No badge found for set of 3 backpacks");
}

void part_2(List *lines) {
    int total = 0;
    while (has_next(lines)) {
        char *one = get_next(lines);
        char *two = get_next(lines);
        char *three = get_next(lines);
        char badge = find_badge(one, two, three);
        total += get_priority(badge);
    }

    printf("part 2: %d\n", total);
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size;

    read_string("../inputs/day_3", &buffer, &buffer_size);
    List *lines = split_by('\n', buffer);

    part_1(lines);
    part_2(lines);
}