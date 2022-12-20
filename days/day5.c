#include "common.h"
#include <stdlib.h>
#include <string.h>

void rev(char *input) {
    size_t start = 0;
    size_t end = strlen(input) - 1;
    while (start < end) {
        char tmp = input[start];
        input[start] = input[end];
        input[end] = tmp;
        start++;
        end--;
    }
}

void split_input(char *input, char **state_buf, char **instructions_buf) {
    char *split = strstr(input, "\n\n");

    size_t state_len = (split - input) + 1;
    char *state = malloc(sizeof(*state) * state_len);
    strncpy(state, input, state_len);
    state[state_len - 1] = '\0';
    *state_buf = state;

    size_t instructions_len = strlen(input) - state_len - 1; // don't include the two newlines, but keep room for 0x0
    char *instructions_start = split + 2; // skip the two newlines to get to the start of the instructions
    char *instructions = malloc(sizeof(*instructions) * instructions_len);
    strncpy(instructions, instructions_start, instructions_len);
    instructions[instructions_len - 1] = '\0';
    *instructions_buf = instructions;
}

size_t stack_count(char *line) {
    rev(line);
    size_t stacks;
    sscanf(line, "%zu", &stacks);
    return stacks;
}

void get_initial_stacks(char *raw_state, List ***stack_array, size_t *n_stacks) {
    List *state_lines = split_by('\n', raw_state);
    reverse(state_lines);

    char *number_line = get_next(state_lines);
    size_t stacks = stack_count(number_line);

    List **s = malloc(sizeof(List *) * stacks);
    for (int i = 0; i < stacks; i++) {
        s[i] = new_list();
    }

    iter_list(state_lines, l, char *) {
        for (int i = 0; i < stacks; i++) {
            char maybe_crate = l[1 + i * 4];
            if (maybe_crate != ' ') {
                char *crate = malloc(sizeof(*crate));
                *crate = maybe_crate;
                push(s[i], crate);
            }
        }
    }

    *n_stacks = stacks;
    *stack_array = s;
    destroy_list(state_lines, 1);
}

void apply_instructions_1(char *instructions_raw, List **stacks) {
    List *instructions = split_by('\n', instructions_raw);
    int n, from, to;
    iter_list(instructions, instruction, char *) {
        sscanf(instruction, "move %d from %d to %d", &n, &from, &to);
        for (int i = 0; i < n; i++) {
            char *crate = pop(stacks[from - 1]);
            push(stacks[to - 1], crate);
        }
    }
    destroy_list(instructions, 1);
}

void apply_instructions_2(char *instructions_raw, List **stacks) {
    List *instructions = split_by('\n', instructions_raw);
    int n, from, to;
    iter_list(instructions, instruction, char *) {
        sscanf(instruction, "move %d from %d to %d", &n, &from, &to);
        char *crates[n];
        for (int i = 0; i < n; i++) {
            crates[i] = (char *) pop(stacks[from - 1]);
        }
        for (int i = n - 1; i >= 0; i--) {
            push(stacks[to - 1], crates[i]);
        }
    }
    destroy_list(instructions, 1);
}

void run_crane(char *raw_input, void (*apply_instructions)(char *instructions_raw, List **stacks)) {
    char *raw_state, *raw_instructions;
    List **stacks;
    size_t num_stacks;

    split_input(raw_input, &raw_state, &raw_instructions);
    get_initial_stacks(raw_state, &stacks, &num_stacks);
    apply_instructions(raw_instructions, stacks);

    free(raw_state);
    free(raw_instructions);
    for (int i = 0; i < num_stacks; i++) {
        char *top_crate = pop(stacks[i]);
        printf("%c", *top_crate);
        free(top_crate);
        destroy_list(stacks[i], 1);
    }
    free(stacks);
    printf("\n");
}

int main(void) {
    char *buf;
    size_t sz;

    read_string("../inputs/day_5", &buf, &sz);
    run_crane(buf, apply_instructions_1);
    run_crane(buf, apply_instructions_2);


    free(buf);
}
