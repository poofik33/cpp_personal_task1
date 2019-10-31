#include "input.h"
#include <stdlib.h>
#include <string.h>


char* input_string(FILE *stream) {
    int buffer_capacity = BUFFER_SIZE;
    char *buffer = (char *)malloc(sizeof(char) * buffer_capacity);
    if (!buffer)
        return NULL;
    char *chunk = (char *)malloc(sizeof(char) * CHUNK_SIZE);
    if (!chunk) {
        free(buffer);
        return NULL;
    }
    char *buffer_p = buffer;
    unsigned int buffer_real_size = 0;
    unsigned int chunk_size = 1;
    chunk[0] = '\0';
    while(chunk[chunk_size - 1] != '\n' && fgets(chunk, CHUNK_SIZE, stream)) {
        chunk_size = strlen(chunk);
        if (buffer_real_size + chunk_size >= buffer_capacity) {
            buffer_capacity *= 2;
            char *new_buffer_p = (char *)realloc(buffer ,sizeof(char) * buffer_capacity);
            if(!new_buffer_p) {
                free(chunk);
                free(buffer);
                return NULL;
            }
            buffer = new_buffer_p;
            buffer_p = buffer + buffer_real_size;
        }
        buffer_real_size += chunk_size;
        memcpy(buffer_p, chunk, chunk_size);
        buffer_p += chunk_size;
    }
    free(chunk);
    char *new_string = (char *)realloc(buffer, sizeof(char) * (buffer_real_size + 1));
    if (!new_string) {
        free(buffer);
        return 0;
    }
    if (!buffer_real_size)
        new_string[buffer_real_size] = '\n';
    else
        new_string[buffer_real_size] = '\0';
    return new_string;
}

int input_number(FILE *stream) {
    char* string = input_string(stream);
    char *end;
    if (!string)
        return 0;
    int return_number = strtol(string, &end, 0);
    free(string);
    return return_number;
}