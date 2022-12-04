#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "list.h"

void read_string(char *path, char **buffer, size_t *buffer_size) {
    FILE *fp = fopen(path, "r");
    char *data = NULL;

    fseek(fp, 0L, SEEK_END);
    size_t file_size = ftell(fp);
    size_t size_with_termination = file_size + 1;
    fseek(fp, 0L, SEEK_SET);

    data = malloc(size_with_termination * sizeof(*data));
    fread(data, sizeof(*data), file_size, fp);
    data[file_size] = 0x00;
    fclose(fp);

    *buffer = data;
    *buffer_size = size_with_termination;
}

LIST *to_lines(char *buf) {
    LIST *list = new_list();

    char *start, *end;
    start = end = buf;

    while ((end = strchr(start, '\n')) != NULL) {
        size_t len = (size_t) (end - start) + 1; // +1 for 0-termination
        char *line = malloc(len * sizeof(*line));

        strncpy(line, start, len - 1);
        line[len - 1] = '\0';
        append(list, line, len);

        start = end + 1;
    }

    return list;
}