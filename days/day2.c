#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "common.h"

#define OPPONENT_ROCK "A"
#define MY_ROCK "X"
#define ROCK_VALUE 1

#define OPPONENT_PAPER "B"
#define MY_PAPER "Y"
#define PAPER_VALUE 2

#define OPPONENT_SCISSORS "C"
#define MY_SCISSORS "Z"
#define SCISSORS_VALUE 3

#define LOSS_VALUE 0
#define DRAW_VALUE 3
#define WIN_VALUE 6

typedef enum Play {
    ROCK,
    PAPER,
    SCISSORS
} Play;

typedef struct Round {
    Play opponent;
    Play me;
} Round;

int score(Round *round) {
    int outcome_score = 0;
    switch (round->opponent) {
        case ROCK:
            if (round->me == SCISSORS) outcome_score = 0;
            if (round->me == ROCK) outcome_score = 3;
            if (round->me == PAPER) outcome_score = 6;
            break;
        case PAPER:
            if (round->me == SCISSORS) outcome_score = 6;
            if (round->me == ROCK) outcome_score = 0;
            if (round->me == PAPER) outcome_score = 3;
            break;
        case SCISSORS:
            if (round->me == SCISSORS) outcome_score = 3;
            if (round->me == ROCK) outcome_score = 6;
            if (round->me == PAPER) outcome_score = 0;
            break;
    }

    int choice_score = 0;
    switch (round->me) {
        case ROCK:
            choice_score = ROCK_VALUE;
            break;
        case PAPER:
            choice_score = PAPER_VALUE;
            break;
        case SCISSORS:
            choice_score = SCISSORS_VALUE;
            break;
    }

    return outcome_score + choice_score;
}

Play to_play(char *raw) {
    if (strcmp(raw, OPPONENT_ROCK) == 0 || strcmp(raw, MY_ROCK) == 0) {
        return ROCK;
    }

    if (strcmp(raw, OPPONENT_PAPER) == 0 || strcmp(raw, MY_PAPER) == 0) {
        return PAPER;
    }

    return SCISSORS;
}

void *score_raw(void *line) {
    int *round_score = malloc(sizeof(*round_score));

    char *l = line;
    List *plays = split_by(' ', l);

    Round round = {
            .opponent = to_play(get_next(plays)),
            .me = to_play(get_next(plays))
    };
    *round_score = score(&round);
    return round_score;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size;

    read_string("../inputs/day_2", &buffer, &buffer_size);

    int score = sum(map(split_by('\n', buffer), score_raw));

    printf("day1, part1: %d\n", score);
}