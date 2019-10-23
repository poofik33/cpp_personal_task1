#ifndef TEST_GTEST_TESTS_H
#define TEST_GTEST_TESTS_H

#include "post.h"

bool initialize_test_bad_input1();

bool initialize_test1();
bool initialize_test2();
bool initialize_test3();
bool initialize_test4();

void destruct_test();

post *test_array;
post *result_array;
size_t post_size;

#endif //TEST_GTEST_TESTS_H
