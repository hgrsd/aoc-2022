#ifndef AOC_2022_COMMON_H
#define AOC_2022_COMMON_H

#include <stdio.h>
#include "list.h"


void read_string(char *path, char **buffer, size_t *buffer_size);
LIST *to_lines(char *buf);

#endif //AOC_2022_COMMON_H
