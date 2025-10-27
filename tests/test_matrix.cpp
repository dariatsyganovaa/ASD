#include <gtest/gtest.h>
#include "../lib_matrix/matrix.h"

TEST(TestMatrixLib, default_constructor) {
    Matrix<int> matr;
    EXPECT_EQ(matr.get_rows(), 0);
    EXPECT_EQ(matr.get_cols(), 0);
    EXPECT_TRUE(matr.is_empty());
}

TEST(TestMatrixLib, size_constructor) {
    Matrix<int> matr(3, 3);
    EXPECT_EQ(matr.get_rows(), 3);
    EXPECT_EQ(matr.get_cols(), 3);
}

TEST(TestMatrixLib, size_constructor_with_zero_init) {
    Matrix<int> matr(3, 3);
    EXPECT_EQ(matr.get_rows(), 3);
    EXPECT_EQ(matr.get_cols(), 3);

    for (size_t i = 0; i < matr.get_rows(); i++) {
        for (size_t j = 0; j < matr.get_cols(); j++) {
            EXPECT_EQ(matr[i][j], 0);
        }
    }
}

TEST(TestMatrixLib, copy_constructor) {
    Matrix<int> matr1(2, 2);
    Matrix<int> matr2(matr1);

    EXPECT_EQ(matr2.get_rows(), 2);
    EXPECT_EQ(matr2.get_cols(), 2);

    for (size_t i = 0; i < matr2.get_rows(); i++) {
        for (size_t j = 0; j < matr2.get_cols(); j++) {
            EXPECT_EQ(matr1[i][j], matr2[i][j]);
        }
    }
}

TEST(TestMatrixLib, copy_null_constructor) {
    Matrix<int> matr1(0, 0);
    Matrix<int> matr2(matr1);

    EXPECT_EQ(matr2.get_rows(), 0);
    EXPECT_EQ(matr2.get_cols(), 0);
    EXPECT_TRUE(matr2.is_empty());
}

TEST(TestMatrixLib, type_conversion_constructor) {
    int arr[3] = { 1, 1, 1 };
    MathVector<int> row1(arr, 3);
    MathVector<int> row2(arr, 3);
    MathVector<int> row3(arr, 3);

    MathVector<MathVector<int>> vec(3);
    vec[0] = row1;
    vec[1] = row2;
    vec[2] = row3;

    Matrix<int> matr(vec);

    EXPECT_EQ(matr.get_rows(), 3);
    EXPECT_EQ(matr.get_cols(), 3);

    for (size_t i = 0; i < matr.get_rows(); i++) {
        for (size_t j = 0; j < matr.get_cols(); j++) {
            EXPECT_EQ(matr[i][j], 1);
        }
    }
}

TEST(TestMatrixLib, get_size) {
    Matrix<int> matr(5, 5);
    EXPECT_EQ(matr.get_rows(), 5);
    EXPECT_EQ(matr.get_cols(), 5);
}

TEST(TestMatrixLib, operator_plus) {
    Matrix<int> matr1(2, 2);
    Matrix<int> matr2(2, 2);

    matr1[0][0] = 1;
    matr1[0][1] = 1;
    matr1[1][0] = 1;
    matr1[1][1] = 1;

    matr2[0][0] = 1;
    matr2[0][1] = 1;
    matr2[1][0] = 1;
    matr2[1][1] = 1;

    Matrix<int> actual_res = matr1 + matr2;
    Matrix<int> expected_res(2, 2);

    expected_res[0][0] = 2;
    expected_res[0][1] = 2;
    expected_res[1][0] = 2;
    expected_res[1][1] = 2;

    EXPECT_EQ(actual_res.get_rows(), expected_res.get_rows());
    EXPECT_EQ(actual_res.get_cols(), expected_res.get_cols());

    for (size_t i = 0; i < expected_res.get_rows(); i++) {
        for (size_t j = 0; j < expected_res.get_cols(); j++) {
            EXPECT_EQ(expected_res[i][j], actual_res[i][j]);
        }
    }
}

TEST(TestMatrixLib, try_operator_plus_with_different_size) {
    Matrix<int> matr1(2, 3);
    Matrix<int> matr2(2, 4);

    EXPECT_THROW(matr1 + matr2, std::invalid_argument);
}

TEST(TestMatrixLib, operator_minus) {
    Matrix<int> matr1(2, 2);
    Matrix<int> matr2(2, 2);

    matr1[0][0] = 2;
    matr1[0][1] = 2;
    matr1[1][0] = 2;
    matr1[1][1] = 2;

    matr2[0][0] = 1;
    matr2[0][1] = 1;
    matr2[1][0] = 1;
    matr2[1][1] = 1;

    Matrix<int> actual_res = matr1 - matr2;
    Matrix<int> expected_res(2, 2);

    expected_res[0][0] = 1;
    expected_res[0][1] = 1;
    expected_res[1][0] = 1;
    expected_res[1][1] = 1;

    EXPECT_EQ(actual_res.get_rows(), expected_res.get_rows());
    EXPECT_EQ(actual_res.get_cols(), expected_res.get_cols());

    for (size_t i = 0; i < expected_res.get_rows(); i++) {
        for (size_t j = 0; j < expected_res.get_cols(); j++) {
            EXPECT_EQ(expected_res[i][j], actual_res[i][j]);
        }
    }
}

TEST(TestMatrixLib, try_operator_minus_with_different_size) {
    Matrix<int> matr1(2, 3);
    Matrix<int> matr2(2, 4);

    EXPECT_THROW(matr1 - matr2, std::invalid_argument);
}

TEST(TestMatrixLib, operator_mult_with_value) {
    Matrix<int> matr1(2, 2);
    int val = 2;

    matr1[0][0] = 2;
    matr1[0][1] = 2;
    matr1[1][0] = 2;
    matr1[1][1] = 2;

    Matrix<int> actual_res = matr1 * val;
    Matrix<int> expected_res(2, 2);

    expected_res[0][0] = 4;
    expected_res[0][1] = 4;
    expected_res[1][0] = 4;
    expected_res[1][1] = 4;

    EXPECT_EQ(actual_res.get_rows(), expected_res.get_rows());
    EXPECT_EQ(actual_res.get_cols(), expected_res.get_cols());

    for (size_t i = 0; i < expected_res.get_rows(); i++) {
        for (size_t j = 0; j < expected_res.get_cols(); j++) {
            EXPECT_EQ(expected_res[i][j], actual_res[i][j]);
        }
    }
}

TEST(TestMatrixLib, operator_mult_with_negative_value) {
    Matrix<int> matr1(2, 2);
    int val = -2;

    matr1[0][0] = 2;
    matr1[0][1] = 2;
    matr1[1][0] = 2;
    matr1[1][1] = 2;

    Matrix<int> actual_res = matr1 * val;
    Matrix<int> expected_res(2, 2);

    expected_res[0][0] = -4;
    expected_res[0][1] = -4;
    expected_res[1][0] = -4;
    expected_res[1][1] = -4;

    EXPECT_EQ(actual_res.get_rows(), expected_res.get_rows());
    EXPECT_EQ(actual_res.get_cols(), expected_res.get_cols());

    for (size_t i = 0; i < expected_res.get_rows(); i++) {
        for (size_t j = 0; j < expected_res.get_cols(); j++) {
            EXPECT_EQ(expected_res[i][j], actual_res[i][j]);
        }
    }
}

TEST(TestMatrixLib, operator_mult_with_vector) {
    int arr1[2] = { 1, 2 };
    MathVector<int> vec1(arr1, 2);

    Matrix<int> matr1(2, 2);
    matr1[0][0] = 2;
    matr1[0][1] = 3;
    matr1[1][0] = 3;
    matr1[1][1] = 2;
    
    int arr2[2] = { 8, 7 };
    MathVector<int> expected_res(arr2, 2);
    MathVector<int> actual_res = matr1 * vec1;

    EXPECT_EQ(actual_res.size(), expected_res.size());

    for (size_t i = 0; i < expected_res.size(); i++) {
        EXPECT_EQ(actual_res[i], expected_res[i]);
    }
}

TEST(TestMatrixLib, try_mult_of_empty_vec_by_matrix) {
    MathVector<int> vec1(0);

    Matrix<int> matr1(2, 2);
    matr1[0][0] = 2;
    matr1[0][1] = 3;
    matr1[1][0] = 3;
    matr1[1][1] = 2;

    EXPECT_THROW(matr1 * vec1, std::invalid_argument);
}

TEST(TestMatrixLib, try_mult_of_vec_by_empty_matrix) {
    int arr1[2] = { 1, 2 };
    MathVector<int> vec1(arr1, 2);

    Matrix<int> matr1(0, 0);

    EXPECT_THROW(matr1 * vec1, std::invalid_argument);
}

TEST(TestMatrixLib, mult_of_vector_by_matrix_with_zero_elements) {
    int arr1[2] = { 0, 2 };
    MathVector<int> vec1(arr1, 2);

    Matrix<int> matr1(2, 2);
    matr1[0][0] = 2;
    matr1[0][1] = 0;
    matr1[1][0] = 3;
    matr1[1][1] = 0;

    int arr2[2] = { 0, 0 };
    MathVector<int> expected_res(arr2, 2);
    MathVector<int> actual_res = matr1 * vec1;

    EXPECT_EQ(actual_res.size(), expected_res.size());

    for (size_t i = 0; i < expected_res.size(); i++) {
        EXPECT_EQ(actual_res[i], expected_res[i]);
    }
}

TEST(TestMatrixLib, matrix_mult) {
    Matrix<int> matr1(2, 2);
    Matrix<int> matr2(2, 2);

    matr1[0][0] = 1;
    matr1[0][1] = 2;
    matr1[1][0] = 3;
    matr1[1][1] = 4;

    matr2[0][0] = 4;
    matr2[0][1] = 3;
    matr2[1][0] = 2;
    matr2[1][1] = 1;

    Matrix<int> actual_res = matr1 * matr2;
    Matrix<int> expected_res(2, 2);

    expected_res[0][0] = 8;
    expected_res[0][1] = 5;
    expected_res[1][0] = 20;
    expected_res[1][1] = 13;

    EXPECT_EQ(actual_res.get_rows(), expected_res.get_rows());
    EXPECT_EQ(actual_res.get_cols(), expected_res.get_cols());

    for (size_t i = 0; i < expected_res.get_rows(); i++) {
        for (size_t j = 0; j < expected_res.get_cols(); j++) {
            EXPECT_EQ(expected_res[i][j], actual_res[i][j]);
        }
    }
}

TEST(TestMatrixLib, try_mult_of_empty_matrices) {
    Matrix<int> matr1(0, 0);
    Matrix<int> matr2(0, 0);

    EXPECT_THROW(matr1 * matr2, std::invalid_argument);
}

TEST(TestMatrixLib, try_operator_mult_with_different_size) {
    Matrix<int> matr1(2, 3);
    Matrix<int> matr2(1, 4);

    EXPECT_THROW(matr1 * matr2, std::invalid_argument);
}

TEST(TestMatrixLib, operator_assignment) {
    Matrix<int> matr1(2, 2);
    Matrix<int> matr2(2, 2);

    matr1[0][0] = 1;
    matr1[0][1] = 2;
    matr1[1][0] = 3;
    matr1[1][1] = 4;

    matr2[0][0] = 4;
    matr2[0][1] = 3;
    matr2[1][0] = 2;
    matr2[1][1] = 1;

    matr1 = matr2;

    EXPECT_EQ(matr1.get_rows(), matr2.get_rows());
    EXPECT_EQ(matr1.get_cols(), matr2.get_cols());

    for (size_t i = 0; i < matr1.get_rows(); i++) {
        for (size_t j = 0; j < matr1.get_cols(); j++) {
            EXPECT_EQ(matr1[i][j], matr2[i][j]);
        }
    }
}

TEST(TestMatrixLib, operator_assignment_with_empty_matrix) {
    Matrix<int> matr1;
    Matrix<int> matr2(2, 2);

    matr2[0][0] = 4;
    matr2[0][1] = 3;
    matr2[1][0] = 2;
    matr2[1][1] = 1;

    matr1 = matr2;

    EXPECT_EQ(matr1.get_rows(), matr2.get_rows());
    EXPECT_EQ(matr1.get_cols(), matr2.get_cols());

    for (size_t i = 0; i < matr1.get_rows(); i++) {
        for (size_t j = 0; j < matr1.get_cols(); j++) {
            EXPECT_EQ(matr1[i][j], matr2[i][j]);
        }
    }
}

TEST(TestMatrixLib, try_operator_assignment_with_different_size) {
    Matrix<int> matr1(2, 2);
    Matrix<int> matr2(1, 2);

    matr1[0][0] = 1;
    matr1[0][1] = 2;
    matr1[1][0] = 3;
    matr1[1][1] = 4;

    matr2[0][0] = 4;
    matr2[0][1] = 3;

    matr1 = matr2;

    EXPECT_EQ(matr1.get_rows(), matr2.get_rows());
    EXPECT_EQ(matr1.get_cols(), matr2.get_cols());

    for (size_t i = 0; i < matr1.get_rows(); i++) {
        for (size_t j = 0; j < matr1.get_cols(); j++) {
            EXPECT_EQ(matr1[i][j], matr2[i][j]);
        }
    }
}

TEST(TestMatrixLib, operator_comparison) {
    Matrix<int> matr1(2, 2);
    Matrix<int> matr2(2, 2);

    matr1[0][0] = 1;
    matr1[0][1] = 1;
    matr1[1][0] = 1;
    matr1[1][1] = 1;

    matr2[0][0] = 1;
    matr2[0][1] = 1;
    matr2[1][0] = 1;
    matr2[1][1] = 1;

    EXPECT_TRUE(matr1 == matr2);
}

TEST(TestMatrixLib, operator_comparison_not_equal) {
    Matrix<int> matr1(2, 3);
    Matrix<int> matr2(1, 2);

    matr1[0][0] = 1;
    matr1[0][1] = 5;
    matr1[0][2] = -4;
    matr1[1][0] = 1;
    matr1[1][1] = 2;
    matr1[1][2] = 3;

    matr2[0][0] = 1;
    matr2[0][1] = 7;

    EXPECT_TRUE(matr1 != matr2);
}

TEST(TestMatrixLib, operator_comparison_not_equal_with_negative_values) {
    Matrix<int> matr1(2, 2);
    Matrix<int> matr2(2, 2);

    matr1[0][0] = 1;
    matr1[0][1] = 1;
    matr1[1][0] = 1;
    matr1[1][1] = 1;

    matr2[0][0] = -1;
    matr2[0][1] = -1;
    matr2[1][0] = -1;
    matr2[1][1] = -1;

    EXPECT_TRUE(matr1 != matr2);
}

TEST(TestMatrixLib, addition_assignment_operator) {
    Matrix<int> matr1(2, 2);
    Matrix<int> matr2(2, 2);

    matr1[0][0] = 1;
    matr1[0][1] = 1;
    matr1[1][0] = 1;
    matr1[1][1] = 1;

    matr2[0][0] = 1;
    matr2[0][1] = 1;
    matr2[1][0] = 1;
    matr2[1][1] = 1;

    Matrix<int> result(2, 2);

    result[0][0] = 2;
    result[0][1] = 2;
    result[1][0] = 2;
    result[1][1] = 2;

    matr1 += matr2;

    for (size_t i = 0; i < matr2.get_rows(); i++) {
        for (size_t j = 0; j < matr2.get_cols(); j++) {
            EXPECT_EQ(matr1[i][j], result[i][j]);
        }
    }
}

TEST(TestMatrixLib, try_addition_assignment_operator_with_different_size) {
    Matrix<int> matr1(1, 2);
    Matrix<int> matr2(2, 2);
    
    matr1[0][0] = 4;
    matr1[0][1] = 3;

    matr2[0][0] = 1;
    matr2[0][1] = 2;
    matr2[1][0] = 3;
    matr2[1][1] = 4;

    EXPECT_THROW(matr1 += matr2, std::invalid_argument);
}

TEST(TestMatrixLib, try_addition_assignment_operator_with_empty_matrix) {
    Matrix<int> matr1(0, 0);
    Matrix<int> matr2(2, 2);

    EXPECT_THROW(matr1 += matr2, std::invalid_argument);
}

TEST(TestMatrixLib, subtraction_assignment_operator) {
    Matrix<int> matr1(2, 2);
    Matrix<int> matr2(2, 2);

    matr1[0][0] = 1;
    matr1[0][1] = 1;
    matr1[1][0] = 1;
    matr1[1][1] = 1;

    matr2[0][0] = 1;
    matr2[0][1] = 1;
    matr2[1][0] = 1;
    matr2[1][1] = 1;

    Matrix<int> result(2, 2);

    result[0][0] = 0;
    result[0][1] = 0;
    result[1][0] = 0;
    result[1][1] = 0;

    matr1 -= matr2;

    for (size_t i = 0; i < matr2.get_rows(); i++) {
        for (size_t j = 0; j < matr2.get_cols(); j++) {
            EXPECT_EQ(matr1[i][j], result[i][j]);
        }
    }
}

TEST(TestMatrixLib, try_subtraction_assignment_operator_with_different_size) {
    Matrix<int> matr1(1, 2);
    Matrix<int> matr2(2, 2);

    matr1[0][0] = 4;
    matr1[0][1] = 3;

    matr2[0][0] = 1;
    matr2[0][1] = 2;
    matr2[1][0] = 3;
    matr2[1][1] = 4;

    EXPECT_THROW(matr1 -= matr2, std::invalid_argument);
}

TEST(TestMatrixLib, subtraction_assignment_operator_with_empty_matrix) {
    Matrix<int> matr1(2, 3);
    Matrix<int> matr2(0, 0);

    EXPECT_THROW(matr1 -= matr2, std::invalid_argument);
}

TEST(TestMatrixLib, multiplication_assignment_operator_with_matrices) {
    Matrix<int> matr1(2, 2);
    Matrix<int> matr2(2, 2);

    matr1[0][0] = 1;
    matr1[0][1] = 2;
    matr1[1][0] = 3;
    matr1[1][1] = 4;

    matr2[0][0] = 4;
    matr2[0][1] = 3;
    matr2[1][0] = 2;
    matr2[1][1] = 1;

    matr1 *= matr2;
    Matrix<int> expected_res(2, 2);

    expected_res[0][0] = 8;
    expected_res[0][1] = 5;
    expected_res[1][0] = 20;
    expected_res[1][1] = 13;

    EXPECT_EQ(matr1.get_rows(), expected_res.get_rows());
    EXPECT_EQ(matr1.get_cols(), expected_res.get_cols());

    for (size_t i = 0; i < expected_res.get_rows(); i++) {
        for (size_t j = 0; j < expected_res.get_cols(); j++) {
            EXPECT_EQ(expected_res[i][j], matr1[i][j]);
        }
    }
}

TEST(TestMatrixLib, try_mult_assignment_operator_with_different_size) {
    Matrix<int> matr1(3, 2);
    Matrix<int> matr2(6, 1);

    EXPECT_THROW(matr1 *= matr2, std::invalid_argument);
}

TEST(TestMatrixLib, multiplication_assignment_operator_with_empty_matrix) {
    Matrix<int> matr1(2, 3);
    Matrix<int> matr2(0, 0);

    EXPECT_THROW(matr1 *= matr2, std::invalid_argument);
}

TEST(TestMatrixLib, multiplication_assignment_operator_with_value) {
    Matrix<int> matr1(2, 2);
    int val = 5;

    matr1[0][0] = 1;
    matr1[0][1] = 2;
    matr1[1][0] = 3;
    matr1[1][1] = 4;

    matr1 *= val;
    Matrix<int> expected_res(2, 2);

    expected_res[0][0] = 5;
    expected_res[0][1] = 10;
    expected_res[1][0] = 15;
    expected_res[1][1] = 20;

    for (size_t i = 0; i < expected_res.get_rows(); i++) {
        for (size_t j = 0; j < expected_res.get_cols(); j++) {
            EXPECT_EQ(expected_res[i][j], matr1[i][j]);
        }
    }
}

TEST(TestMatrixLib, mult_by_value_assignment_operator_with_zero) {
    Matrix<int> matr1(2, 2);
    int val = 5;

    matr1 *= val;

    for (size_t i = 0; i < matr1.get_rows(); i++) {
        for (size_t j = 0; j < matr1.get_cols(); j++) {
            EXPECT_EQ(matr1[i][j], 0);
        }
    }
}

TEST(TestMatrixLib, multiplication_assignment_operator_with_negative_value) {
    Matrix<int> matr1(2, 2);
    int val = -5;

    matr1[0][0] = 1;
    matr1[0][1] = 2;
    matr1[1][0] = 3;
    matr1[1][1] = 4;

    matr1 *= val;
    Matrix<int> expected_res(2, 2);

    expected_res[0][0] = -5;
    expected_res[0][1] = -10;
    expected_res[1][0] = -15;
    expected_res[1][1] = -20;

    for (size_t i = 0; i < expected_res.get_rows(); i++) {
        for (size_t j = 0; j < expected_res.get_cols(); j++) {
            EXPECT_EQ(expected_res[i][j], matr1[i][j]);
        }
    }
}

TEST(TestMatrixLib, access_operator) {
    Matrix<int> matr1(2, 2);

    matr1[0][0] = 1;
    matr1[0][1] = 2;
    matr1[1][0] = 3;
    matr1[1][1] = 4;

    EXPECT_EQ(matr1[0][0], 1);
    EXPECT_EQ(matr1[0][1], 2);
    EXPECT_EQ(matr1[1][0], 3);
    EXPECT_EQ(matr1[1][1], 4);
}

//TEST(TestMatrixLib, commutativity_of_the_operator) {
//    Matrix<int> matr1(2, 2);
//    Matrix<int> matr2(2, 2);
//
//    matr1[0][0] = 1;
//    matr1[0][1] = 2;
//    matr1[1][0] = 3;
//    matr1[1][1] = 4;
//
//    matr2[0][0] = 4;
//    matr2[0][1] = 3;
//    matr2[1][0] = 2;
//    matr2[1][1] = 1;
//
//    Matrix<int> result1 = matr1 * matr2;
//    Matrix<int> result2 = matr2 * matr1;
//
//    EXPECT_EQ(result1, result2);
//}

TEST(TestMatrixLib, matrix_mult_vector_as_matrix_multiplication) {
    Matrix<int> matr1(2, 2);
    matr1[0][0] = 1;
    matr1[0][1] = 2;
    matr1[1][0] = 3;
    matr1[1][1] = 4;

    Matrix<int> matr2(2, 1);
    matr2[0][0] = 5;
    matr2[1][0] = 6;

    Matrix<int> result = matr1 * matr2;

    EXPECT_EQ(result.get_rows(), 2);
    EXPECT_EQ(result.get_cols(), 1);

    EXPECT_EQ(result[0][0], 17);
    EXPECT_EQ(result[1][0], 39);

    MathVector<int> result_vector(result.get_rows());
    for (size_t i = 0; i < result.get_rows(); i++) {
        result_vector[i] = result[i][0];
    }

    EXPECT_EQ(result_vector.size(), 2);
    EXPECT_EQ(result_vector[0], 17);
    EXPECT_EQ(result_vector[1], 39);
}

TEST(TestMatrixLib, simple_mixed_assignment_addition) {
    Matrix<int> matr1(2, 2);
    matr1[0][0] = 1;
    matr1[0][1] = 2;
    matr1[1][0] = 3;
    matr1[1][1] = 4;

    Matrix<int> matr2(matr1);
    matr2 += matr1;

    EXPECT_EQ(matr2[0][0], 2);
    EXPECT_EQ(matr2[0][1], 4);
    EXPECT_EQ(matr2[1][0], 6);
    EXPECT_EQ(matr2[1][1], 8);
}