#ifndef TEST_GTEST_INPUT_H
#define TEST_GTEST_INPUT_H

#include <stdio.h>
#include <time.h>

#define BUFFER_SIZE 512
#define CHUNK_SIZE 64

char* input_string(FILE *stream);
int input_number(FILE *stream);

#endif //TEST_GTEST_INPUT_H
