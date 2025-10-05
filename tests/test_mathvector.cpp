#include <gtest/gtest.h>
#include "../lib_mathvector/mathvector.h"

TEST(TestMathVectorLib, default_constructor) {
    MathVector<int> vec;
    EXPECT_TRUE((vec.size() == (size_t)0) && (vec.is_empty() == true) && (vec.start_index() == (size_t)0));
}

TEST(TestMathVectorLib, size_constructor) {
    MathVector<int> vec(7);
    EXPECT_EQ(vec.size(), 7);
    EXPECT_EQ(vec.capacity(), 15);
    EXPECT_EQ(vec.start_index(), 0);

    for (size_t i = 0; i < vec.capacity(); i++) {
        EXPECT_EQ(vec.states()[i], empty);
    }
}

TEST(TestMathVectorLib, size_constructor_with_start_index) {
    MathVector<int> vec(7, 0);
    EXPECT_EQ(vec.size(), 7);
    EXPECT_EQ(vec.capacity(), 15);
    EXPECT_EQ(vec.start_index(), 0);

    for (size_t i = 0; i < vec.capacity(); i++) {
        EXPECT_EQ(vec.states()[i], empty);
    }
}

TEST(TestMathVectorLib, copy_constructor) {
    MathVector<int> vec1(9);
    MathVector<int> vec2(vec1);

    EXPECT_EQ(vec2.size(), 9);
    EXPECT_EQ(vec2.capacity(), 15);

    for (size_t i = 0; i < vec2.size(); i++) {
        EXPECT_EQ(vec1.data()[i], vec2.data()[i]);
    }
}

TEST(TestMathVectorLib, copy_null_constructor) {
    MathVector<int> vec1(0);
    MathVector<int> vec2(vec1);

    EXPECT_EQ(vec2.size(), 0);
    EXPECT_EQ(vec2.capacity(), 0);
    EXPECT_TRUE(vec2.is_empty() == true);
}

TEST(TestMathVectorLib, mass_constructor) {
    int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    MathVector<int> vec(arr, 9);

    EXPECT_EQ(vec.size(), 9);
    EXPECT_EQ(vec.capacity(), 15);

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_EQ(vec.data()[i], arr[i]);
        EXPECT_EQ(vec.states()[i], busy);
    }
}

TEST(TestMathVectorLib, mass_null_constructor) {
    int* arr = nullptr;
    MathVector<int> vec(arr, 0);

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_TRUE(vec.is_empty() == true);
}

TEST(TestMathVectorLib, destructor) {
    MathVector<int> vec2;
    vec2.push_back_elem(1);
}

TEST(TestMathVectorLib, get_start_index) {
    MathVector<int> vec1(15);

    EXPECT_EQ(vec1.size(), 15);
    EXPECT_EQ(vec1.start_index(), 0);
}

TEST(TestMathVectorLib, get_size) {
    MathVector<int> vec(5);
    EXPECT_EQ(vec.size(), 5);

    MathVector<int> empty_vec(0);
    EXPECT_EQ(empty_vec.size(), 0);
}

TEST(TestMathVectorLib, operator_plus) {
    int arr1[5] = { 1, 2, 3, 4, 5 };
    int arr2[5] = { 1, 2, 3, 4, 5 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 5);

    int expected_res[5] = { 2, 4, 6, 8, 10 };
    MathVector<int> actual_res = vec1 + vec2;

    EXPECT_EQ(actual_res.size(), 5);

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(expected_res[i], actual_res[i]);
    }
}

TEST(TestMathVectorLib, try_operator_plus_with_different_size) {
    int arr1[3] = { 1, 2, 3 };
    int arr2[5] = { 1, 2, 3, 4, 5 };

    MathVector<int> vec1(arr1, 3);
    MathVector<int> vec2(arr2, 5);

    EXPECT_THROW(vec1 + vec2, std::invalid_argument);
}

TEST(TestMathVectorLib, operator_minus) {
    int arr1[5] = { 2, 4, 6, 8, 10 };
    int arr2[5] = { 1, 2, 3, 4, 5 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 5);

    int expected_res[5] = { 1, 2, 3, 4, 5 };
    MathVector<int> actual_res = vec1 - vec2;

    EXPECT_EQ(actual_res.size(), 5);

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(expected_res[i], actual_res[i]);
    }
}

TEST(TestMathVectorLib, try_operator_minus_with_different_size) {
    int arr1[5] = { 1, 2, 3, 4, 5 };
    int arr2[3] = { 1, 2, 3 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 3);

    EXPECT_THROW(vec1 - vec2, std::invalid_argument);
}

TEST(TestMathVectorLib, operator_mult_with_value) {
    int arr[5] = { 1, 2, 3, 4, 5 };
    int val = 2;

    MathVector<int> vec1(arr, 5);

    int expected_res[5] = { 2, 4, 6, 8, 10 };
    MathVector<int> actual_res = vec1 * val;

    EXPECT_EQ(actual_res.size(), 5);

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(expected_res[i], actual_res[i]);
    }
}

TEST(TestMathVectorLib, operator_mult_with_negative_value) {
    int arr[5] = { 1, 2, 3, 4, 5 };
    int val = -2;

    MathVector<int> vec1(arr, 5);

    int expected_res[5] = { -2, -4, -6, -8, -10 };
    MathVector<int> actual_res = vec1 * val;

    EXPECT_EQ(actual_res.size(), 5);

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(expected_res[i], actual_res[i]);
    }
}

TEST(TestMathVectorLib, operator_mult_with_vector) {
    int arr1[5] = { 1, 2, 1, 2, 1 };
    int arr2[5] = { 1, 2, 3, 4, 5 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 5);

    int expected_res = 21;
    int actual_res = vec1 * vec2;

    EXPECT_EQ(expected_res, actual_res);
}

TEST(TestMathVectorLib, mult_operator_with_zero_elems) {
    int arr1[5] = { 1, 0, 1, 0, 1 };
    int arr2[5] = { 0, 2, 0, 4, 0 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 5);

    int expected_res = 0;
    int actual_res = vec1 * vec2;

    EXPECT_EQ(expected_res, actual_res);
}

TEST(TestMathVectorLib, mult_of_empty_vectors) {
    MathVector<int> vec1(0);
    MathVector<int> vec2(0);

    int expected_res = 0;
    int actual_res = vec1 * vec2;

    EXPECT_EQ(expected_res, actual_res);
}

TEST(TestMathVectorLib, try_operator_mult_with_different_size) {
    int arr1[5] = { 1, 2, 3, 4, 5 };
    int arr2[3] = { 1, 2, 3 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 3);

    EXPECT_THROW(vec1 * vec2, std::invalid_argument);
}

TEST(TestMathVectorLib, operator_assignment) {
    int arr1[5] = { 1, 2, 1, 2, 1 };
    int arr2[5] = { 1, 2, 3, 4, 5 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 5);

    vec1 = vec2;

    EXPECT_EQ(vec1.size(), vec2.size());

    for (size_t i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(vec1[i], vec2[i]);
    }
}

TEST(TestMathVectorLib, operator_assignment_with_empty_vec) {
    int arr1[5] = { 1, 2, 3, 4, 5 };

    MathVector<int> vec1;
    MathVector<int> vec2(arr1, 5);

    vec1 = vec2;

    EXPECT_EQ(vec1.size(), vec2.size());

    for (size_t i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(vec1[i], vec2[i]);
    }
}

TEST(TestMathVectorLib, try_operator_assignment_with_different_size) {
    int arr1[5] = { 1, 2, 3, 4, 5 };
    int arr2[3] = { 1, 2, 3 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 3);

    vec1 = vec2;

    EXPECT_EQ(vec1.size(), vec2.size());

    for (size_t i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(vec1[i], vec2[i]);
    }
}

TEST(TestMathVectorLib, operator_comparison) {
    int arr1[5] = { 1, 2, 3, 4, 5 };
    int arr2[5] = { 1, 2, 3, 4, 5 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 5);

    EXPECT_TRUE(vec1 == vec2);
}

TEST(TestMathVectorLib, operator_comparison_not_equal) {
    int arr1[5] = { 5, 4, 1, 2, 3 };
    int arr2[5] = { 1, 2, 3, 4, 5 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 5);

    EXPECT_TRUE(vec1 != vec2);
}

TEST(TestMathVectorLib, operator_comparison_not_equal_with_negative_values) {
    int arr1[5] = { 1, 2, 3, 4, 5 };
    int arr2[5] = { -1, -2, -3, -4, -5 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 5);

    EXPECT_TRUE(vec1 != vec2);
}

TEST(TestMathVectorLib, addition_assignment_operator) {
    int arr1[5] = { 5, 4, 1, 2, 3 };
    int arr2[5] = { 1, 2, 3, 4, 5 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 5);

    int expected_res[5] = { 6, 6, 4, 6, 8 };
    vec1 += vec2;

    for (int i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(expected_res[i], vec1[i]);
    }

    EXPECT_EQ(vec1.size(), vec2.size());
}

TEST(TestMathVectorLib, try_addition_assignment_operator_with_different_size) {
    int arr2[5] = { 5, 4, 1, 2, 3 };

    MathVector<int> vec1;
    MathVector<int> vec2(arr2, 5);

    EXPECT_THROW(vec1 += vec2, std::invalid_argument);
}

TEST(TestMathVectorLib, addition_assignment_operator_with_empty_vec) {
    int arr2[5] = { 5, 4, 1, 2, 3 };

    MathVector<int> vec1(5);
    MathVector<int> vec2(arr2, 5);

    int expected_res[5] = { 5, 4, 1, 2, 3 };
    vec1 += vec2;

    for (int i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(expected_res[i], vec1[i]);
    }

    EXPECT_EQ(vec1.size(), vec2.size());
}

TEST(TestMathVectorLib, subtraction_assignment_operator) {
    int arr1[5] = { 5, 4, 1, 2, 3 };
    int arr2[5] = { 1, 2, 3, 4, 5 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 5);

    int expected_res[5] = { 4, 2, -2, -2, -2 };
    vec1 -= vec2;

    for (int i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(expected_res[i], vec1[i]);
    }

    EXPECT_EQ(vec1.size(), vec2.size());
}

TEST(TestMathVectorLib, try_subtraction_assignment_operator_with_different_size) {
    int arr1[5] = { 5, 4, 1, 2, 3 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2;

    EXPECT_THROW(vec1 -= vec2, std::invalid_argument);
}

TEST(TestMathVectorLib, subtraction_assignment_operator_with_empty_vec) {
    int arr1[5] = { 5, 4, 1, 2, 3 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(5);

    int expected_res[5] = { 5, 4, 1, 2, 3 };
    vec1 -= vec2;

    for (int i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(expected_res[i], vec1[i]);
    }

    EXPECT_EQ(vec1.size(), vec2.size());
}

TEST(TestMathVectorLib, multiplication_assignment_operator_with_vec) {
    int arr1[5] = { 1, 1, 1, 1, 1 };
    int arr2[5] = { 1, 2, 3, 4, 5 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 5);

    int expected_res[5] = { 1, 2, 3, 4, 5 };
    vec1 *= vec2;

    for (int i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(expected_res[i], vec1[i]);
    }

    EXPECT_EQ(vec1.size(), vec2.size());
}

TEST(TestMathVectorLib, try_multiplication_assignment_operator_with_different_size) {
    int arr2[5] = { 5, 4, 1, 2, 3 };

    MathVector<int> vec1;
    MathVector<int> vec2(arr2, 5);

    EXPECT_THROW(vec1 *= vec2, std::invalid_argument);
}

TEST(TestMathVectorLib, multiplication_assignment_operator_with_empty_vec) {
    int arr2[5] = { 5, 4, 1, 2, 3 };

    MathVector<int> vec1(5);
    MathVector<int> vec2(arr2, 5);

    int expected_res[5] = { 0, 0, 0, 0, 0 };
    vec1 *= vec2;

    for (int i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(expected_res[i], vec1[i]);
    }

    EXPECT_EQ(vec1.size(), vec2.size());
}

TEST(TestMathVectorLib, multiplication_assignment_operator_with_value) {
    int arr1[5] = { 1, 1, 1, 1, 1 };
    int val = 5;

    MathVector<int> vec1(arr1, 5);

    int expected_res[5] = { 5, 5, 5, 5, 5 };
    vec1 *= val;

    for (int i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(expected_res[i], vec1[i]);
    }

    EXPECT_EQ(vec1.size(), 5);
}

TEST(TestMathVectorLib, mult_assignment_operator_with_empty_vec) {
    MathVector<int> vec1(5);
    int val = 5;
    int expected_res[5] = { 0, 0, 0, 0, 0 };
    vec1 *= val;

    for (int i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(expected_res[i], vec1[i]);
    }

    EXPECT_EQ(vec1.size(), 5);
}

TEST(TestMathVectorLib, multiplication_assignment_operator_with_negative_value) {
    int arr[5] = { 1, 2, 3, 4, 5 };
    int val = -2;

    MathVector<int> vec1(arr, 5);

    int expected_res[5] = { -2, -4, -6, -8, -10 };
    vec1 *= val;

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(expected_res[i], vec1[i]);
    }

    EXPECT_EQ(vec1.size(), 5);
}

TEST(TestMathVectorLib, access_operator) {
    int arr[5] = { 5, 4, 1, 2, 3 };

    MathVector<int> vec(arr, 5);

    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 4);
    EXPECT_EQ(vec[2], 1);
    EXPECT_EQ(vec[3], 2);
    EXPECT_EQ(vec[4], 3);
}

TEST(TestMathVectorLib, commutativity_of_the_operator) {
    int arr1[5] = { 5, 4, 1, 2, 3 };
    int arr2[5] = { 1, 2, 3, 4, 5 };

    MathVector<int> vec1(arr1, 5);
    MathVector<int> vec2(arr2, 5);
    
    int result1 = vec1 * vec2;
    int result2 = vec2 * vec1;
    EXPECT_EQ(result1, result2);
}

