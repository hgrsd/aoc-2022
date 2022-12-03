#ifndef AOC_2022_COMMON_H
#define AOC_2022_COMMON_H

#include <stdio.h>
#include "node.h"


void read_string(char *path, char **buffer, size_t *buffer_size);
NODE *read_lines(char *buf);

#endif //AOC_2022_COMMON_H
