#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"

TEST(TestAlgorithmsLib, try_find_local_minimum_of_a_matrix) {
    Matrix<int> matr1(3, 4);

    ASSERT_ANY_THROW(local_minimum_of_a_matrix(matr1));
}

TEST(TestAlgorithmsLib, find_local_minimum_of_a_matrix) {
    Matrix<int> matr1(3, 3);
    matr1[0][0] = 11;
    matr1[0][1] = 4;
    matr1[0][2] = 5;
    matr1[1][0] = 2;
    matr1[1][1] = 3;
    matr1[1][2] = 6;
    matr1[2][0] = 7;
    matr1[2][1] = 8;
    matr1[2][2] = 9;

    EXPECT_EQ(local_minimum_of_a_matrix(matr1), 2);
}

TEST(TestAlgorithmsLib, find_local_minimum_of_a_matrix_2) {
    Matrix<int> matr1(4, 4);
    matr1[0][0] = 11;
    matr1[0][1] = 15;
    matr1[0][2] = 10;
    matr1[0][3] = 9;
    matr1[1][0] = 6;
    matr1[1][1] = 16;
    matr1[1][2] = 3;
    matr1[1][3] = 8;
    matr1[2][0] = 7;
    matr1[2][1] = 4;
    matr1[2][2] = 2;
    matr1[2][3] = 13;
    matr1[3][0] = 14;
    matr1[3][1] = 12;
    matr1[3][2] = 1;
    matr1[3][3] = 5;

    int val = local_minimum_of_a_matrix(matr1);
    EXPECT_TRUE(val == 6 || val == 1);
}
