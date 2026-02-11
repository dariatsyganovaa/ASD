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

TEST(TestAlgorithmsLib, try_check_breckets_1) {
    std::string str = "()()";

    EXPECT_TRUE(check_breckets(str));
}

TEST(TestAlgorithmsLib, try_check_breckets_2) {
    std::string str = "[(()())({})]";

    EXPECT_TRUE(check_breckets(str));
}

TEST(TestAlgorithmsLib, try_check_breckets_3) {
    std::string str = "(()()";

    EXPECT_FALSE(check_breckets(str));
}

TEST(TestAlgorithmsLib, try_check_breckets_4) {
    std::string str = "())(())";

    EXPECT_FALSE(check_breckets(str));
}

TEST(TestAlgorithmsLib, try_check_breckets_5) {
    std::string str = "((()()(()))";

    EXPECT_FALSE(check_breckets(str));
}

TEST(TestAlgorithmsLib, try_read_expression_1) {
    EXPECT_NO_THROW(read_expression("3 * (15 + (x + y) * (2*x - 7*y^2))"));
    EXPECT_ANY_THROW(read_expression("3 * (15 + (x y) * (2x - 7*y^2))"));
    EXPECT_ANY_THROW(read_expression("3 * (15 + (x + y) * (2*x - 7*y^))"));
    EXPECT_ANY_THROW(read_expression("3 * (15 + (x + y) * (2*x - 7*y^2)"));
    EXPECT_ANY_THROW(read_expression("3 * (15 + (x + y) * (2*x - 7*y^2)))"));
}

TEST(TestAlgorithmsLib, rabbit_turtle_has_cycle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    Node<int>* head = list.head();
    Node<int>* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    Node<int>* cycle = head->next->next;
    tail->next = cycle;

    EXPECT_TRUE(is_looped_rabbit_turtle(&list));

    tail->next = nullptr;
}

TEST(TestAlgorithmsLib, reversal_check_has_cycle) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    Node<int>* head = list.head();
    Node<int>* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    tail->next = head;

    EXPECT_TRUE(is_looped(&list));

    tail->next = nullptr;
}

TEST(TestAlgorithmsLib, find_loop_detects_entry_point) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    Node<int>* head = list.head();
    Node<int>* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }
    Node<int>* expected_entry = head->next->next;

    tail->next = expected_entry;

    Node<int>* result = find_loop(&list);
    EXPECT_EQ(result, expected_entry);
    EXPECT_EQ(result->data, 3);

    tail->next = nullptr;
}

TEST(TestAlgorithmsLib, find_loop_returns_null_if_no_cycle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    Node<int>* result = find_loop(&list);
    EXPECT_EQ(result, nullptr);
}

TEST(TestAlgorithmsLib, counting_of_islands_complex) {
    Matrix<int> matr1(4, 4);

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++) matr1[i][j] = 0;

    matr1[0][1] = 1;

    matr1[2][0] = 1;
    matr1[3][0] = 1;
    matr1[2][2] = 1; matr1[2][3] = 1;
    matr1[3][2] = 1;

    int val = count_of_islands(matr1);
    EXPECT_EQ(val, 3);
}

TEST(TestAlgorithmsLib, counting_of_islands_full_square) {
    Matrix<int> matr(2, 2);

    matr[0][0] = 1; matr[0][1] = 1;
    matr[1][0] = 1; matr[1][1] = 1;

    int val = count_of_islands(matr);

    EXPECT_EQ(val, 1);
}

TEST(TestAlgorithmsLib, counting_of_islands) {
    Matrix<int> matr(2, 2);

    matr[0][0] = 1; matr[0][1] = 0;
    matr[1][0] = 0; matr[1][1] = 0;

    int val = count_of_islands(matr);

    EXPECT_EQ(val, 1);
}