//
// Created by poofik on 20.10.2019.
//

#include "input.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* input_string() {
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
    while(chunk[chunk_size - 1] != '\n' && fgets(chunk, CHUNK_SIZE, stdin)) {
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

struct tm * input_date() {
    char* date_string_p = NULL;
    char* tmp = input_string();
    if (!tmp)
        return NULL;
    date_string_p = (char *)realloc(tmp, sizeof(char) * DATE__FORMAT_SIZE + 1);
    date_string_p[DATE__FORMAT_SIZE] = '\0';
    if(strlen(date_string_p) != DATE__FORMAT_SIZE) {
        free(date_string_p);
        return NULL;
    }
    tmp = date_string_p;
    bool correct_date_input = 1;
    char* str_int = (char *)malloc(sizeof(char) * (DAY_FORMAT + 1));
    if (!str_int) {
        free(date_string_p);
        return NULL;
    }
    memcpy(str_int, tmp, 2);
    str_int[DAY_FORMAT] = '\0';
    int day = atoi(str_int);
    correct_date_input = correct_date_input && (day <= MAX_DAY_VALUE || day >= MIN_DAY_VALUE);
    tmp += DAY_FORMAT + 1;
    memcpy(str_int, tmp, 2);
    str_int[MONTH_FORMAT] = '\0';
    int month = atoi(str_int);
    correct_date_input = correct_date_input && (month <= MAX_MONTH_VALUE || month >= MIN_MONTH_VALUE);
    tmp += MONTH_FORMAT + 1;
    char* str_year = realloc(str_int, sizeof(char) * (YEAR_FORMAT + 1));
    if (!str_year) {
        free(date_string_p);
        free(str_int);
        return NULL;
    }
    str_int = str_year;
    memcpy(str_int, tmp, 4);
    str_int[YEAR_FORMAT] = '\0';
    int year = atoi(str_int);
    correct_date_input = correct_date_input && (year >= MIN_YEAR_VALUE);
    if (!correct_date_input) {
        free(str_int);
        free(date_string_p);
        return NULL;
    }
    struct tm *date = (struct tm *)malloc(sizeof(struct tm));
    if (!date) {
        free(str_int);
        free(date_string_p);
        return NULL;
    }
    struct tm tmp_date = {
            .tm_year = year - 1900,
            .tm_mon = month - 1,
            .tm_mday = day
    };
    *date = tmp_date;
    free(str_int);
    free(date_string_p);
    return date;
}

int input_number() {
    char* string = input_string();
    char *end;
    if (!string)
        return 0;
    int return_number = strtol(string, &end, 0);
    free(string);
    return return_number;
}