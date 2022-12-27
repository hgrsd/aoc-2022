#include <stddef.h>
#include <stdlib.h>
#include "common.h"

#define VALUES_BUF_SIZE 400

int execute(char *instruction, int *x_cycles, int current_cycle) {
    char op[5];
    int n;
    sscanf(instruction, "%s %d", op, &n);

    // noop
    if (op[0] == 'n') {
        x_cycles[current_cycle + 1] = x_cycles[current_cycle];
        return 1;
    }

    // else: addx
    x_cycles[current_cycle + 1] = x_cycles[current_cycle];
    x_cycles[current_cycle + 2] = x_cycles[current_cycle] + n;
    return 2;
}

void run_instructions(List *instructions, int *x_cycles) {
    for (int i = 0; i < VALUES_BUF_SIZE; i++) {
        x_cycles[i] = 1;
    }
    int n_cycle = 1;

    iter_list(instructions, instruction, char *) {
        n_cycle = n_cycle + execute(instruction, x_cycles, n_cycle);
    }
    rewind_list(instructions);
}

void part1(const int *x_values) {
    printf("day 10, part 1: %d\n",
           (x_values[20] * 20) + (x_values[60] * 60) + (x_values[100] * 100) + (x_values[140] * 140) +
           (x_values[180] * 180) + (x_values[220] * 220));
}

void part2(const int *x_values) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 40; j++) {
            int idx = i * 40 + j + 1;
            int sprite[3] = {x_values[idx] - 1, x_values[idx], x_values[idx] + 1};
            if (sprite[0] == j || sprite[1] == j || sprite[2] == j) {
                printf("X");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

int main(void) {
    char *buf;
    size_t sz;

    read_string("../inputs/day_10", &buf, &sz);
    List *lines = split_by('\n', buf);

    int x_values[VALUES_BUF_SIZE];
    run_instructions(lines, x_values);

    part1(x_values);
    part2(x_values);

    destroy_list(lines, 1);
    free(buf);
}