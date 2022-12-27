#include <stdlib.h>
#include "common.h"

int one_contains_other(int start0, int end0, int start1, int end1) {
    return (start0 <= start1 && end0 >= end1) || (start1 <= start0 && end1 >= end0);
}

int has_overlap(int start0, int end0, int start1, int end1) {
    return one_contains_other(start0, end0, start1, end1)
           || (start0 <= start1 && end0 >= start1)
           || (start1 <= start0 && end1 >= start0);
}

int sum_with(List *lines, int(*get_value)(int, int, int, int)) {
    int sum = 0;
    iter_list(lines, line, char *) {
        int elf1_start, elf1_end, elf2_start, elf2_end;
        sscanf(line, "%d-%d,%d-%d", &elf1_start, &elf1_end, &elf2_start, &elf2_end);
        sum += get_value(elf1_start, elf1_end, elf2_start, elf2_end);
    }

    return sum;
}

int main(void) {
    char *buf;
    size_t sz;

    read_string("../inputs/day_4", &buf, &sz);
    List *lines = split_by('\n', buf);
    free(buf);

    int part_1 = sum_with(lines, one_contains_other);
    rewind_list(lines);
    int part_2 = sum_with(lines, has_overlap);

    printf("day 4, part 1: %d\n", part_1);
    printf("day 4, part 2: %d\n", part_2);
    destroy_list(lines, 1);
}