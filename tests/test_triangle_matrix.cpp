#include <gtest/gtest.h>
#include "../lib_triangle_matrix/triangle_matrix.h"

TEST(TestTriangleMatrixLib, default_constructor) {
    TriangleMatrix<int> matr;
    EXPECT_EQ(matr.get_size(), 0);
    EXPECT_TRUE(matr.is_empty());
}

TEST(TestTriangleMatrixLib, size_constructor) {
    TriangleMatrix<int> matr(3);
    EXPECT_EQ(matr.get_size(), 3);
}

TEST(TestTriangleMatrixLib, size_constructor_with_zero_init) {
    TriangleMatrix<int> matr(3);
    EXPECT_EQ(matr.get_size(), 3);

    for (size_t i = 0; i < matr.get_size(); i++) {
        for (size_t j = i; j < matr.get_size(); j++) {
            EXPECT_EQ(matr[i][j], 0);
        }
    }
}

TEST(TestTriangleMatrixLib, copy_constructor) {
    TriangleMatrix<int> matr1(3);
    TriangleMatrix<int> matr2(matr1);
    EXPECT_EQ(matr2.get_size(), 3);

    for (size_t i = 0; i < matr2.get_size(); i++) {
        for (size_t j = i; j < matr2.get_size(); j++) {
            EXPECT_EQ(matr1[i][j], matr2[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, copy_null_constructor) {
    TriangleMatrix<int> matr1(0);
    TriangleMatrix<int> matr2(matr1);

    EXPECT_EQ(matr2.get_size(), 0);
    EXPECT_TRUE(matr2.is_empty());
}

TEST(TestTriangleMatrixLib, type_conversion_constructor) {
    Matrix<int> matr1(2, 2);
    matr1[0][0] = 1; matr1[0][1] = 2;
    matr1[1][0] = 3; matr1[1][1] = 4;

    TriangleMatrix<int> matr2(matr1);

    for (size_t i = 0; i < matr2.get_size(); i++) {
        for (size_t j = i; j < matr2.get_size(); j++) {
            EXPECT_EQ(matr1[i][j], matr2[i][j]);
        }
    }
    EXPECT_EQ(matr2.get_size(), 2);
}

TEST(TestTriangleMatrixLib, try_type_conversion_constructor_with_different_sizes) {
    Matrix<int> matr1(3, 4);
    EXPECT_THROW(TriangleMatrix<int> matr2(matr1), std::invalid_argument);
}

TEST(TestTriangleMatrixLib, get_size) {
    TriangleMatrix<int> matr(3);
    EXPECT_EQ(matr.get_size(), 3);
}

TEST(TestTriangleMatrixLib, operator_plus) {
    TriangleMatrix<int> matr1(2);
    TriangleMatrix<int> matr2(2);

    matr1[0][0] = 1; matr1[0][1] = 1; matr1[1][1] = 1;
    matr2[0][0] = 1; matr2[0][1] = 1; matr2[1][1] = 1;

    TriangleMatrix<int> actual_res = matr1 + matr2;
    TriangleMatrix<int> expected_res(2);

    expected_res[0][0] = 2; expected_res[0][1] = 2; expected_res[1][1] = 2;

    EXPECT_EQ(actual_res.get_size(), expected_res.get_size());

    for (size_t i = 0; i < expected_res.get_size(); i++) {
        for (size_t j = i; j < expected_res.get_size(); j++) {
            EXPECT_EQ(expected_res[i][j], actual_res[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, operator_minus) {
    TriangleMatrix<int> matr1(2);
    TriangleMatrix<int> matr2(2);

    matr1[0][0] = 2; matr1[0][1] = 2; matr1[1][1] = 2;
    matr2[0][0] = 1; matr2[0][1] = 1; matr2[1][1] = 1;

    TriangleMatrix<int> actual_res = matr1 - matr2;
    TriangleMatrix<int> expected_res(2);

    expected_res[0][0] = 1; expected_res[0][1] = 1; expected_res[1][1] = 1;

    EXPECT_EQ(actual_res.get_size(), expected_res.get_size());

    for (size_t i = 0; i < expected_res.get_size(); i++) {
        for (size_t j = i; j < expected_res.get_size(); j++) {
            EXPECT_EQ(expected_res[i][j], actual_res[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, try_operator_plus_minus_mult_with_different_size) {
    TriangleMatrix<int> matr1(2);
    TriangleMatrix<int> matr2(3);

    EXPECT_THROW(matr1 + matr2, std::invalid_argument);
    EXPECT_THROW(matr1 - matr2, std::invalid_argument);
    EXPECT_THROW(matr1 * matr2, std::invalid_argument);
}

TEST(TestTriangleMatrixLib, try_mult_of_empty_matrices) {
    TriangleMatrix<int> matr1(0);
    TriangleMatrix<int> matr2(0);

    EXPECT_THROW(matr1 * matr2, std::invalid_argument);
}

TEST(TestTriangleMatrixLib, operator_mult_with_value) {
    TriangleMatrix<int> matr1(2);
    int val = 2;

    matr1[0][0] = 2; matr1[0][1] = 2; matr1[1][1] = 2;

    TriangleMatrix<int> actual_res = matr1 * val;
    TriangleMatrix<int> expected_res(2);

    expected_res[0][0] = 4; expected_res[0][1] = 4; expected_res[1][1] = 4;

    EXPECT_EQ(actual_res.get_size(), expected_res.get_size());

    for (size_t i = 0; i < expected_res.get_size(); i++) {
        for (size_t j = i; j < expected_res.get_size(); j++) {
            EXPECT_EQ(expected_res[i][j], actual_res[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, operator_mult_with_negative_value) {
    TriangleMatrix<int> matr1(2);
    int val = -2;

    matr1[0][0] = 2; matr1[0][1] = 2; matr1[1][1] = 2;

    TriangleMatrix<int> actual_res = matr1 * val;
    TriangleMatrix<int> expected_res(2);

    expected_res[0][0] = -4; expected_res[0][1] = -4; expected_res[1][1] = -4;

    EXPECT_EQ(actual_res.get_size(), expected_res.get_size());

    for (size_t i = 0; i < expected_res.get_size(); i++) {
        for (size_t j = i; j < expected_res.get_size(); j++) {
            EXPECT_EQ(expected_res[i][j], actual_res[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, operator_mult_with_vector) {
    int arr1[2] = { 1, 2 };
    MathVector<int> vec1(arr1, 2);

    TriangleMatrix<int> matr1(2);
    matr1[0][0] = 2; matr1[0][1] = 2; matr1[1][1] = 2;

    int arr2[2] = { 6, 4 };
    MathVector<int> expected_res(arr2, 2);
    MathVector<int> actual_res = matr1 * vec1;

    EXPECT_EQ(actual_res.size(), expected_res.size());

    for (size_t i = 0; i < expected_res.size(); i++) {
        EXPECT_EQ(actual_res[i], expected_res[i]);
    }
}

TEST(TestTriangleMatrixLib, operator_mult_with_empty_vector) {
    TriangleMatrix<int> matr(3);

    matr[0][0] = 1; matr[0][1] = 1; matr[0][2] = 1;
    matr[1][1] = 1; matr[1][2] = 1;
    matr[2][2] = 1;

    int arr1[3] = { 0, 0, 0 };
    MathVector<int> vec(arr1, 3);

    MathVector<int> actual_res = matr * vec;
    MathVector<int> expected_res(arr1, 3);

    for (size_t i = 0; i < expected_res.size(); i++) {
        EXPECT_EQ(expected_res[i], actual_res[i]);
    }
}

TEST(TestTriangleMatrixLib, try_mult_of_empty_vec_by_tri_matrix) {
    MathVector<int> vec1(0);

    TriangleMatrix<int> matr1(2);
    matr1[0][0] = 2; matr1[0][1] = 2; matr1[1][1] = 2;

    EXPECT_THROW(matr1 * vec1, std::invalid_argument);
}

TEST(TestTriangleMatrixLib, try_mult_of_vec_by_empty_matrix) {
    int arr1[2] = { 1, 2 };
    MathVector<int> vec1(arr1, 2);

    TriangleMatrix<int> matr1(0);

    EXPECT_THROW(matr1 * vec1, std::invalid_argument);
}

TEST(TestTriangleMatrixLib, mult_of_vector_by_matrix_with_zero_elements) {
    int arr1[2] = { 0, 2 };
    MathVector<int> vec1(arr1, 2);

    TriangleMatrix<int> matr1(2);
    matr1[0][0] = 1; matr1[0][1] = 0; matr1[1][1] = 1;

    int arr2[2] = { 0, 2 };
    MathVector<int> expected_res(arr2, 2);
    MathVector<int> actual_res = matr1 * vec1;

    EXPECT_EQ(actual_res.size(), expected_res.size());

    for (size_t i = 0; i < expected_res.size(); i++) {
        EXPECT_EQ(actual_res[i], expected_res[i]);
    }
}

TEST(TestTriangleMatrixLib, matrix_mult) {
    TriangleMatrix<int> matr1(2);
    TriangleMatrix<int> matr2(2);

    matr1[0][0] = 2; matr1[0][1] = 2; matr1[1][1] = 2;
    matr2[0][0] = 1; matr2[0][1] = 1; matr2[1][1] = 1;

    TriangleMatrix<int> actual_res = matr1 * matr2;
    TriangleMatrix<int> expected_res(2);

    expected_res[0][0] = 2; expected_res[0][1] = 4; expected_res[1][1] = 2;

    EXPECT_EQ(actual_res.get_size(), expected_res.get_size());

    for (size_t i = 0; i < expected_res.get_size(); i++) {
        for (size_t j = i; j < expected_res.get_size(); j++) {
            EXPECT_EQ(expected_res[i][j], actual_res[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, operator_assignment) {
    TriangleMatrix<int> matr1(3);
    TriangleMatrix<int> matr2(3);

    matr1[0][0] = 1; matr1[0][1] = 1; matr1[0][2] = 1;
    matr1[1][1] = 1; matr1[1][2] = 1;
    matr1[2][2] = 1;

    matr2[0][0] = 1; matr2[0][1] = 2; matr2[0][2] = 3;
    matr2[1][1] = 2; matr2[1][2] = 3;
    matr2[2][2] = 3;

    matr1 = matr2;

    EXPECT_EQ(matr1.get_rows(), matr2.get_rows());
    EXPECT_EQ(matr1.get_cols(), matr2.get_cols());

    for (size_t i = 0; i < matr1.get_rows(); i++) {
        for (size_t j = i; j < matr1.get_cols(); j++) {
            EXPECT_EQ(matr1[i][j], matr2[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, operator_assignment_with_empty_matrix) {
    TriangleMatrix<int> matr1;
    TriangleMatrix<int> matr2(2);

    matr2[0][0] = 3; matr2[0][1] = 2;
    matr2[1][1] = 1;

    matr1 = matr2;

    EXPECT_EQ(matr1.get_rows(), matr2.get_rows());
    EXPECT_EQ(matr1.get_cols(), matr2.get_cols());

    for (size_t i = 0; i < matr1.get_rows(); i++) {
        for (size_t j = i; j < matr1.get_cols(); j++) {
            EXPECT_EQ(matr1[i][j], matr2[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, try_operator_assignment_with_different_size) {
    TriangleMatrix<int> matr1(3);
    TriangleMatrix<int> matr2(2);

    matr1[0][0] = 1; matr1[0][1] = 1; matr1[0][2] = 1;
    matr1[1][1] = 1; matr1[1][2] = 1;
    matr1[2][2] = 1;

    matr2[0][0] = 1; matr2[0][1] = 2; 
    matr2[1][1] = 2; 

    matr1 = matr2;

    EXPECT_EQ(matr1.get_rows(), matr2.get_rows());
    EXPECT_EQ(matr1.get_cols(), matr2.get_cols());

    for (size_t i = 0; i < matr1.get_rows(); i++) {
        for (size_t j = i; j < matr1.get_cols(); j++) {
            EXPECT_EQ(matr1[i][j], matr2[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, operator_comparison) { 
    TriangleMatrix<int> matr1(2);
    TriangleMatrix<int> matr2(2);

    matr1[0][0] = 1; matr1[0][1] = 1;
    matr1[1][1] = 1;

    matr2[0][0] = 1; matr2[0][1] = 1;
    matr2[1][1] = 1;

    EXPECT_TRUE(matr1 == matr2);
    EXPECT_FALSE(matr1 != matr2);
}

TEST(TestTriangleMatrixLib, operator_comparison_not_equal) {
    TriangleMatrix<int> matr1(3);
    TriangleMatrix<int> matr2(2);

    matr1[0][0] = 1; matr1[0][1] = 1; matr1[0][2] = 1;
    matr1[1][1] = 1; matr1[1][2] = 1;
    matr1[2][2] = 1;

    matr1[0][0] = 1; matr1[0][1] = 1;
    matr1[1][1] = 1; 

    EXPECT_TRUE(matr1 != matr2);
    EXPECT_FALSE(matr1 == matr2);
}

TEST(TestTriangleMatrixLib, operator_comparison_not_equal_with_negative_values) {
    TriangleMatrix<int> matr1(2);
    TriangleMatrix<int> matr2(2);

    matr1[0][0] = 1; matr1[0][1] = 1;
    matr1[1][1] = 1;

    matr2[0][0] = -1; matr2[0][1] = -1;
    matr2[1][1] = -1;

    EXPECT_TRUE(matr1 != matr2);
}

TEST(TestTriangleMatrixLib, addition_assignment_operator) {
    TriangleMatrix<int> matr1(2);
    TriangleMatrix<int> matr2(2);

    matr1[0][0] = 1; matr1[0][1] = 1;
    matr1[1][1] = 1;

    matr2[0][0] = 1; matr2[0][1] = 1;
    matr2[1][1] = 1;

    TriangleMatrix<int> result(2);

    result[0][0] = 2; result[0][1] = 2;
    result[1][1] = 2;

    matr1 += matr2;

    for (size_t i = 0; i < matr2.get_rows(); i++) {
        for (size_t j = i; j < matr2.get_cols(); j++) {
            EXPECT_EQ(matr1[i][j], result[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, try_add_sub_mult_assignment_operator_with_different_size) {
    TriangleMatrix<int> matr1(3);
    TriangleMatrix<int> matr2(2);

    matr1[0][0] = 1; matr1[0][1] = 1; matr1[0][2] = 1;
    matr1[1][1] = 1; matr1[1][2] = 1;
    matr1[2][2] = 1;

    matr2[0][0] = 1; matr2[0][1] = 2;
    matr2[1][1] = 2;

    EXPECT_THROW(matr1 += matr2, std::invalid_argument);
    EXPECT_THROW(matr1 -= matr2, std::invalid_argument);
    EXPECT_THROW(matr1 *= matr2, std::invalid_argument);
}

TEST(TestTriangleMatrixLib, try_add_sub_mult_assignment_operator_with_empty_matrix) {
    TriangleMatrix<int> matr1;
    TriangleMatrix<int> matr2(2);

    EXPECT_THROW(matr1 += matr2, std::invalid_argument);
    EXPECT_THROW(matr1 -= matr2, std::invalid_argument);
    EXPECT_THROW(matr1 *= matr2, std::invalid_argument);
}

TEST(TestTriangleMatrixLib, subtraction_assignment_operator) {
    TriangleMatrix<int> matr1(2);
    TriangleMatrix<int> matr2(2);

    matr1[0][0] = 1; matr1[0][1] = 1;
    matr1[1][1] = 1;

    matr2[0][0] = 1; matr2[0][1] = 1;
    matr2[1][1] = 1;

    TriangleMatrix<int> result(2);

    result[0][0] = 0; result[0][1] = 0;
    result[1][1] = 0;

    matr1 -= matr2;

    for (size_t i = 0; i < matr2.get_rows(); i++) {
        for (size_t j = i; j < matr2.get_cols(); j++) {
            EXPECT_EQ(matr1[i][j], result[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, multiplication_assignment_operator_with_matrices) {
    TriangleMatrix<int> matr1(2);
    TriangleMatrix<int> matr2(2);

    matr1[0][0] = 1; matr1[0][1] = 2;
    matr1[1][1] = 3;

    matr2[0][0] = 3; matr2[0][1] = 2;
    matr2[1][1] = 1;

    matr1 *= matr2;
    TriangleMatrix<int> expected_res(2);

    expected_res[0][0] = 3; expected_res[0][1] = 4;
    expected_res[1][1] = 3;

    EXPECT_EQ(matr1.get_rows(), expected_res.get_rows());
    EXPECT_EQ(matr1.get_cols(), expected_res.get_cols());

    for (size_t i = 0; i < expected_res.get_rows(); i++) {
        for (size_t j = i; j < expected_res.get_cols(); j++) {
            EXPECT_EQ(expected_res[i][j], matr1[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, multiplication_assignment_operator_with_value) {
    TriangleMatrix<int> matr1(2);
    int val = 5;

    matr1[0][0] = 1; matr1[0][1] = 2;
    matr1[1][1] = 3;

    matr1 *= val;
    TriangleMatrix<int> expected_res(2);

    expected_res[0][0] = 5; expected_res[0][1] = 10;
    expected_res[1][1] = 15;

    for (size_t i = 0; i < expected_res.get_rows(); i++) {
        for (size_t j = i; j < expected_res.get_cols(); j++) {
            EXPECT_EQ(expected_res[i][j], matr1[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, mult_by_value_assignment_operator_with_zero) {
    TriangleMatrix<int> matr1(2);
    int val = 5;

    matr1 *= val;

    for (size_t i = 0; i < matr1.get_rows(); i++) {
        for (size_t j = i; j < matr1.get_cols(); j++) {
            EXPECT_EQ(matr1[i][j], 0);
        }
    }
}

TEST(TestTriangleMatrixLib, multiplication_assignment_operator_with_negative_value) {
    TriangleMatrix<int> matr1(2);
    int val = -5;

    matr1[0][0] = 1; matr1[0][1] = 2;
    matr1[1][1] = 3;

    matr1 *= val;
    Matrix<int> expected_res(2, 2);

    expected_res[0][0] = -5; expected_res[0][1] = -10;
    expected_res[1][1] = -15;

    for (size_t i = 0; i < expected_res.get_rows(); i++) {
        for (size_t j = i; j < expected_res.get_cols(); j++) {
            EXPECT_EQ(expected_res[i][j], matr1[i][j]);
        }
    }
}

TEST(TestTriangleMatrixLib, simple_mixed_assignment_addition) {
    TriangleMatrix<int> matr1(2);
    matr1[0][0] = 1; matr1[0][1] = 2;
    matr1[1][1] = 3;

    TriangleMatrix<int> matr2(matr1);
    matr2 += matr1;

    EXPECT_EQ(matr2[0][0], 2);
    EXPECT_EQ(matr2[0][1], 4);
    EXPECT_EQ(matr2[1][1], 6);
}