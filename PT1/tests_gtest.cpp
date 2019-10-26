#include <gtest/gtest.h>

extern "C" {
#include "post.h"
#include "tests.h"
};

TEST(BAD_INPUT, input_1_post) {
    bool success = initialize_test_bad_input1();
    if (success) {
        size_t return_size = 0;
        const post **result = get_popular_posts(test_array, post_size, &return_size);
        EXPECT_EQ(return_size, 1);
        EXPECT_EQ(test_array->name, result_array->name);
        free(result);
    }
    destruct_test();
}

TEST(BAD_INPUT, input_0_post) {
    post *test_post = nullptr;
    const post **result = get_popular_posts(test_post, 0, nullptr);
    EXPECT_EQ(result, nullptr);
}

// actual_content / users_content
TEST(CORRECT_INPUT, TEST1) {
    //post1 - 10/10, post2 - 6/6, post3 - 0/0
    bool success = initialize_test1();
    if (success) {
        size_t return_size = 0;
        const post **result = get_popular_posts(test_array, post_size, &return_size);
        EXPECT_EQ(return_size, 2);
        EXPECT_EQ(result[0]->name, result_array[0].name) << "Should be post1";
        EXPECT_EQ(result[1]->name, result_array[1].name) << "Should be post2";
        free(result);
    }
    destruct_test();
}

TEST(CORRECT_INPUT, TEST2) {
    //post1 - 3/10, post2 - 6/6, post3 - 5/6
    bool success = initialize_test2();
    if (success) {
        size_t return_size = 0;
        const post **result = get_popular_posts(test_array, post_size, &return_size);
        EXPECT_EQ(return_size, 2);
        EXPECT_EQ(result[0]->name, result_array[0].name) << "Should be post2";
        EXPECT_EQ(result[1]->name, result_array[1].name) << "Should be post3";
        free(result);
    }
    destruct_test();
}

TEST(CORRECT_INPUT, TEST3) {
    //post1 - 0/10, post2 - 4/4, post3 - 2/2
    bool success = initialize_test3();
    if (success) {
        size_t return_size = 0;
        const post **result = get_popular_posts(test_array, post_size, &return_size);
        EXPECT_EQ(return_size, 2);
        EXPECT_EQ(result[0]->name, result_array[0].name) << "Should be post2";
        EXPECT_EQ(result[1]->name, result_array[1].name) << "Should be post3";
        free(result);
    }
    destruct_test();
}

TEST(CORRECT_INPUT, TEST4) {
    //post1 - 0/0, post2 - 0/0, post3 - 0/0
    bool success = initialize_test4();
    if (success) {
        size_t return_size = 0;
        const post **result = get_popular_posts(test_array, post_size, &return_size);
        EXPECT_EQ(return_size, 2);
        EXPECT_EQ(result[0]->name, result_array[0].name) << "Should be post3";
        EXPECT_EQ(result[1]->name, result_array[1].name) << "Should be post2";
        free(result);
    }
    destruct_test();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}