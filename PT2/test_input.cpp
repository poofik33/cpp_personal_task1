#include <cstring>
#include <fstream>
#include <gtest/gtest.h>

extern "C" {
    #include "input.h"
}

TEST(FUNCTIONAL_TEST, INPUT_STRING_TEST) {
    std::ofstream test_file;
    test_file.open("test.txt");
    test_file << "test_string";
    test_file.close();

    FILE *test_file_c = fopen("test.txt", "r");
    char *test_string = input_string(test_file_c);
    EXPECT_EQ(strcmp(test_string, "test_string"), 0);

    free(test_string);
    fclose(test_file_c);
    remove("test.txt");
}

TEST(FUNCTIONAL_TEST, INPUT_STRINGS_TEST) {
    std::ofstream test_file;
    test_file.open("test.txt");
    test_file << "test_string1\ntest_string2";
    test_file.close();

    FILE *test_file_c = fopen("test.txt", "r");
    char *test_string = input_string(test_file_c);
    EXPECT_EQ(strcmp(test_string, "test_string1\n"), 0);
    free(test_string);
    test_string = input_string(test_file_c);
    EXPECT_EQ(strcmp(test_string, "test_string2"), 0);

    free(test_string);
    fclose(test_file_c);
    remove("test.txt");
}

TEST(FUNCTIONAL_TEST, INPUT_NUMBER_TEST) {
    std::ofstream test_file;
    test_file.open("test.txt");
    test_file << "150";
    test_file.close();

    FILE *test_file_c = fopen("test.txt", "r");
    int test_number = input_number(test_file_c);
    EXPECT_EQ(test_number, 150);
    
    fclose(test_file_c);
    remove("test.txt");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
