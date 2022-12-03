#include <stdio.h>
#include <malloc.h>

void read_string(char *path, char **buffer, size_t *buffer_size) {
    FILE *fp = fopen(path, "r");
    char *data = NULL;

    fseek(fp, 0L, SEEK_END);
    size_t file_size = ftell(fp);
    size_t size_with_termination = file_size + 1;
    fseek(fp, 0L, SEEK_SET);

    data = (char *) malloc(size_with_termination * sizeof(char));
    fread(data, sizeof(char), file_size, fp);
    data[file_size] = 0x00;
    fclose(fp);

    *buffer = data;
    *buffer_size = size_with_termination;
}
