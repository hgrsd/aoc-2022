#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define OPPONENT_ROCK "A"
#define MY_ROCK "X"
#define SHOULD_LOSE "X"
#define ROCK_VALUE 1

#define OPPONENT_PAPER "B"
#define MY_PAPER "Y"
#define SHOULD_DRAW "Y"
#define PAPER_VALUE 2

#define OPPONENT_SCISSORS "C"
#define MY_SCISSORS "Z"
#define SHOULD_WIN "Z"
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
            if (round->me == SCISSORS) outcome_score = LOSS_VALUE;
            if (round->me == ROCK) outcome_score = DRAW_VALUE;
            if (round->me == PAPER) outcome_score = WIN_VALUE;
            break;
        case PAPER:
            if (round->me == SCISSORS) outcome_score = WIN_VALUE;
            if (round->me == ROCK) outcome_score = LOSS_VALUE;
            if (round->me == PAPER) outcome_score = DRAW_VALUE;
            break;
        case SCISSORS:
            if (round->me == SCISSORS) outcome_score = DRAW_VALUE;
            if (round->me == ROCK) outcome_score = WIN_VALUE;
            if (round->me == PAPER) outcome_score = LOSS_VALUE;
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

Play parse_as_play(char *raw_instruction) {
    if (strcmp(raw_instruction, OPPONENT_ROCK) == 0 || strcmp(raw_instruction, MY_ROCK) == 0) {
        return ROCK;
    }

    if (strcmp(raw_instruction, OPPONENT_PAPER) == 0 || strcmp(raw_instruction, MY_PAPER) == 0) {
        return PAPER;
    }

    return SCISSORS;
}

Play get_my_turn_1(Play *opponent_play, char *raw_instruction) {
    return parse_as_play(raw_instruction);
}

Play get_my_turn_2(Play *opponent_play, char *raw_instruction) {
    if (strcmp(raw_instruction, SHOULD_DRAW) == 0) {
        return *opponent_play;
    }

    if (strcmp(raw_instruction, SHOULD_WIN) == 0) {
        switch (*opponent_play) {
            case ROCK:
                return PAPER;
            case PAPER:
                return SCISSORS;
            default:
                return ROCK;
        }
    }

    switch (*opponent_play) {
        case ROCK:
            return SCISSORS;
        case PAPER:
            return ROCK;
        default:
            return PAPER;
    }

}

void *score_inner(void *line, Play (*decode_instruction)(Play *, char *)) {
    int *round_score = malloc(sizeof(*round_score));

    char *l = line;
    List *instructions = split_by(' ', l);

    Play opponent_play = parse_as_play(get_next(instructions));
    Round round = {
            .opponent = opponent_play,
            .me = decode_instruction(&opponent_play, get_next(instructions))
    };
    *round_score = score(&round);
    return round_score;
}

void *score_raw_1(void *line) {
    return score_inner(line, get_my_turn_1);
}

void *score_raw_2(void *line) {
    return score_inner(line, get_my_turn_2);
}


int main(void) {
    char *buffer = NULL;
    size_t buffer_size;

    read_string("../inputs/day_2", &buffer, &buffer_size);

    List *lines = split_by('\n', buffer);
    free(buffer);

    List *scores_1 = map(lines, score_raw_1);
    printf("day1, part1: %d\n", sum(scores_1));
    destroy_list(scores_1, 1);

    List *scores_2 = map(lines, score_raw_2);
    printf("day1, part2: %d\n", sum(scores_2));
    destroy_list(scores_2, 1);
}