#include <fstream>
#include <gtest/gtest.h>

extern "C" {
    #include "matrix.h"
}
                                      //can be matrix 4x6
int matrix_6x4[24] = { 1,  2,  3,  4, // 1,  2,  3,  4,  5,  6,
                       5,  6,  7,  8, // 7,  8,  9, 10, 11, 12,
                       9, 10, 11, 12, //13, 14, 15, 16, 17, 18,
                      13, 14, 15, 16, //19, 20, 21, 22, 23, 24
                      17, 18, 19, 20,
                      21, 22, 23, 24};

int check_matrix_6x4[24] = { 1,  2,  3,  4,
                             5,  6,  7,  8,
                            24, 23, 22, 12,
                            20, 19, 15, 17,
                            16, 18, 14, 13,
                            21, 11, 10,  9};

int check_matrix_4x6[24] = {22, 21, 20,  4,  5,  6,
                            16, 15,  9, 13, 11, 12,
                            10, 14,  8,  7, 17, 18,
                            19,  3,  2,  1, 23, 24};

TEST(BAD_INPUT, null_ptr) {
    bool success = side_matrix_reflection(NULL, 2, 2);
    EXPECT_FALSE(success);
}

TEST(BAD_INPUT, zero_width) {
    int *matrix = new int[4];
    bool success = side_matrix_reflection(matrix, 0, 2);
    EXPECT_FALSE(success);
    delete[] matrix;
}

TEST(BAD_INPUT, zero_heigth) {
    int *matrix = new int[4];
    bool success = side_matrix_reflection(matrix, 2, 0);
    EXPECT_FALSE(success);
    delete[] matrix;
}

TEST(INPUT_TEST, testing_input_function) {
    std::ofstream test_file;
    test_file.open("test.txt");
    test_file << "3\n4\n";
    for (int i = 1; i < 13; i++)
        test_file << i << std::endl;
    test_file.close();

    FILE *test_file_c = fopen("test.txt", "r");
    size_t test_width, test_heigth;
    int *test_matrix = nullptr;
    input_matrix(&test_matrix, &test_width, &test_heigth, test_file_c);
    EXPECT_EQ(test_width, 3);
    EXPECT_EQ(test_heigth, 4);
    for (int i = 0; i < 12; i++)
        EXPECT_EQ(test_matrix[i], i+1);

    free(test_matrix);
    fclose(test_file_c);
    remove("test.txt");
}

TEST(FUNCTIONAL_TEST, matrix_2x2) {
    int *matrix = new int[4];
    for (int i = 0; i < 4; i++)
        matrix[i] = i+1;
    bool success = side_matrix_reflection(matrix, 2, 2);
    if (success) {
        int check_matrix[4] = {4, 2, 3, 1};
        for (int i = 0; i < 4; i++)
            EXPECT_EQ(check_matrix[i],matrix[i]);
    } else
        EXPECT_TRUE(success);
    delete [] matrix;
}

TEST(FUNCTIONAL_TEST, matrix_6x4) {
    int *matrix = new int[24];
    for (int i = 0; i < 24; i++)
        matrix[i] = i+1;
    bool success = side_matrix_reflection(matrix, 4, 6);
    if (success) {
        for (int i = 0; i < 24; i++)
            EXPECT_EQ(check_matrix_6x4[i],matrix[i]);
    } else
        EXPECT_TRUE(success);
    delete [] matrix;
}

TEST(FUNCTIONAL_TEST, matrix_4x6) {
    int *matrix = new int[24];
    for (int i = 0; i < 24; i++)
        matrix[i] = i+1;
    bool success = side_matrix_reflection(matrix, 6, 4);
    if (success) {
        for (int i = 0; i < 24; i++)
            EXPECT_EQ(check_matrix_4x6[i],matrix[i]);
    } else
        EXPECT_TRUE(success);
    delete [] matrix;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
