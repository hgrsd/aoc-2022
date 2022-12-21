#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"
#include "common.h"

int scenic_score(int **grid, int row, int col, size_t n_rows, size_t n_cols) {
    int current_tree = grid[row][col];

    // looking left
    int left = 0;
    for (int i = col - 1; i >= 0; i--) {
        left++;
        if (grid[row][i] >= current_tree) {
            break;
        }
    }

    // looking right
    int right = 0;
    for (int i = col + 1; i < n_cols; i++) {
        right++;
        if (grid[row][i] >= current_tree) {
            break;
        }
    }

    // looking up
    int up = 0;
    for (int i = row - 1; i >= 0; i--) {
        up++;
        if (grid[i][col] >= current_tree) {
            break;
        }
    }

    // looking down
    int down = 0;
    for (int i = row + 1; i < n_rows; i++) {
        down++;
        if (grid[i][col] >= current_tree) {
            break;
        }
    }

    return left * right * up * down;
}

int is_visible(int **grid, int row, int col, size_t n_rows, size_t n_cols) {
    int current_tree = grid[row][col];
    int has_bigger_tree = 0;

    // horizontal visibility
    for (int i = 0; i < col; i++) {
        if (grid[row][i] >= current_tree) {
            has_bigger_tree = 1;
        }
    }
    if (has_bigger_tree == 0) return 1;

    has_bigger_tree = 0;
    for (int i = col + 1; i < n_cols; i++) {
        if (grid[row][i] >= current_tree) {
            has_bigger_tree = 1;
        }
    }
    if (has_bigger_tree == 0) return 1;

    // vertical visibility
    has_bigger_tree = 0;
    for (int i = 0; i < row; i++) {
        if (grid[i][col] >= current_tree) {
            has_bigger_tree = 1;
        }
    }
    if (has_bigger_tree == 0) return 1;

    has_bigger_tree = 0;
    for (int i = row + 1; i < n_rows; i++) {
        if (grid[i][col] >= current_tree) {
            has_bigger_tree = 1;
        }
    }
    if (has_bigger_tree == 0) return 1;
    return 0;

}

struct Args {
    int **grid;
    size_t n_rows;
    size_t n_cols;
};

void *day8_part1(void *args) {
    struct Args *a = args;
    int total = 0;
    for (int i = 0; i < a->n_rows; i++) {
        for (int j = 0; j < a->n_cols; j++) {
            total += is_visible(a->grid, i, j, a->n_rows, a->n_cols);
        }
    }
    printf("day 8, part 1: %d\n", total);
    return NULL;
}

void *day8_part2(void *args) {
    struct Args *a = args;
    int max_score = 0;
    for (int i = 0; i < a->n_rows; i++) {
        for (int j = 0; j < a->n_cols; j++) {
            int score = scenic_score(a->grid, i, j, a->n_rows, a->n_cols);
            if (score > max_score) max_score = score;
        }
    }
    printf("day 8, part 2: %d\n", max_score);
    return NULL;
}

int **initialize_grid(List *lines, size_t *n_rows, size_t *n_cols) {
    char *first_line = lines->head->data;
    size_t cols = strlen(first_line);
    size_t rows = lines->len;

    int **grid = malloc(sizeof(*grid) * rows);

    int current_row = 0;
    iter_list(lines, line, char *) {
        grid[current_row] = malloc(sizeof(**grid) * cols);
        for (int i = 0; i < cols; i++) {
            char *c = line + i;
            grid[current_row][i] = *c - 48;
        }
        current_row++;
    }

    *n_rows = rows;
    *n_cols = cols;
    return grid;
}

int main(void) {
    char *buf;
    size_t sz;


    read_string("../inputs/day_8", &buf, &sz);
    List *lines = split_by('\n', buf);

    size_t n_rows, n_cols;
    int **grid = initialize_grid(lines, &n_rows, &n_cols);

    struct Args args = {
        .n_rows = n_rows,
        .n_cols = n_cols,
        .grid = grid
    };

    pthread_t tid0;
    pthread_create(&tid0, NULL, day8_part1, (void *)&args);
    pthread_t tid1;
    pthread_create(&tid1, NULL, day8_part2, (void *)&args);
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);


    destroy_list(lines, 1);
    free(buf);
    for (int i = 0; i < n_rows; i++) {
        free(grid[i]);
    }
    free(grid);
}
