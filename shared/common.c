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

static void append_chunk(const char *start, const char *end, List *list) {
    size_t len = (size_t) (end - start) + 1; // +1 for 0-termination
    char *token = malloc(len * sizeof(*token));

    strncpy(token, start, len - 1);
    token[len - 1] = '\0';
    append(list, token);
}

List *split_by(char sep, char *buf) {
    List *list = new_list();

    char *start, *end;
    start = end = buf;

    while ((end = strchr(start, sep)) != NULL) {
        append_chunk(start, end, list);
        start = end + 1;
    }

    // if we're not yet at the end of the string, but no further delimiter is present, append the last bit to the list
    if (start < buf + strlen(buf)) {
        end = buf + strlen(buf);
        append_chunk(start, end, list);
    }

    return list;
}
