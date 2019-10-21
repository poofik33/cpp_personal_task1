//
// Created by poofik on 20.10.2019.
//

#ifndef TEST_GTEST_INPUT_H
#define TEST_GTEST_INPUT_H

#include <time.h>

#define BUFFER_SIZE 512
#define CHUNK_SIZE 64

#define DATE__FORMAT_SIZE 10
#define DAY_FORMAT 2
#define MONTH_FORMAT 2
#define YEAR_FORMAT 4

#define MIN_DAY_VALUE 1
#define MAX_DAY_VALUE 31
#define MIN_MONTH_VALUE 1
#define MAX_MONTH_VALUE 12
#define MIN_YEAR_VALUE 1900

char* input_string();
struct tm * input_date();
int input_number();

#endif //TEST_GTEST_INPUT_H
