#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include "common.h"

typedef struct Coordinate {
    int x;
    int y;
} Coordinate;

Coordinate *coordinate(int x, int y) {
    Coordinate *c = malloc(sizeof(*c));
    c->x = x;
    c->y = y;
    return c;
}

Coordinate *move_tail(Coordinate *head_position, Coordinate *tail_position) {
    int x_delta = head_position->x - tail_position->x;
    int y_delta = head_position->y - tail_position->y;

    if (abs(x_delta) <= 1 && abs(y_delta) <= 1) {
        return coordinate(tail_position->x, tail_position->y);
    }

    if (x_delta == 0) {
        return coordinate(tail_position->x, tail_position->y + abs(y_delta) / y_delta);
    }

    if (y_delta == 0) {
        return coordinate(tail_position->x + abs(x_delta) / x_delta, tail_position->y);
    }

    return coordinate(tail_position->x + abs(x_delta) / x_delta, tail_position->y + abs(y_delta) / y_delta);
}

int push_if_unique(List *coordinates, Coordinate *coordinate) {
    iter_list(coordinates, c, Coordinate *) {
        if (c->x == coordinate->x && c->y == coordinate->y) {
            rewind_list(coordinates);
            return 0;
        }
    }
    rewind_list(coordinates);
    push_back(coordinates, coordinate);
    return 1;
}

void part1(List *lines) {
    Coordinate *head = coordinate(0, 0);
    Coordinate *tail = coordinate(0, 0);
    List *tail_visited = new_list();
    push_back(tail_visited, tail);

    char direction;
    int n;

    iter_list(lines, line, char *) {
        sscanf(line, "%c %d", &direction, &n);
        for (int i = 0; i < n; i++) {
            switch (direction) {
                case 'U':
                    head = coordinate(head->x, head->y + 1);
                    break;
                case 'D':
                    head = coordinate(head->x, head->y - 1);
                    break;
                case 'L':
                    head = coordinate(head->x - 1, head->y);
                    break;
                case 'R':
                    head = coordinate(head->x + 1, head->y);
                    break;
                default:
                    assert("Unreachable");

            }
            tail = move_tail(head, tail);
            push_if_unique(tail_visited, tail);
        }
    }
    rewind_list(lines);
    printf("day 9, part 1: %zu\n", tail_visited->len);
}

void part2(List *lines) {
    Coordinate *knots[10];
    List *tail_visited = new_list();

    for (int i = 0; i < 10; i++) {
        knots[i] = coordinate(0, 0);
    }

    push_back(tail_visited, knots[9]);

    char direction;
    int n;

    iter_list(lines, line, char *) {
        sscanf(line, "%c %d", &direction, &n);
        for (int i = 0; i < n; i++) {
            Coordinate *cur = knots[0];
            switch (direction) {
                case 'U':
                    knots[0] = coordinate(cur->x, cur->y + 1);
                    break;
                case 'D':
                    knots[0] = coordinate(cur->x, cur->y - 1);
                    break;
                case 'L':
                    knots[0] = coordinate(cur->x - 1, cur->y);
                    break;
                case 'R':
                    knots[0] = coordinate(cur->x + 1, cur->y);
                    break;
                default:
                    assert("Unreachable");
            }
            for (int j = 1; j < 10; j++ ) {
                knots[j] = move_tail(knots[j - 1], knots[j]);
            }
            push_if_unique(tail_visited, knots[9]);
        }
    }
    rewind_list(lines);
    printf("day 9, part 2: %zu\n", tail_visited->len);
}

int main(void) {
    char *buf;
    size_t sz;

    read_string("../inputs/day_9", &buf, &sz);

    List *lines = split_by('\n', buf);
    part1(lines);
    part2(lines);
}