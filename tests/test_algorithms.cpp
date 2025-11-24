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

//TEST(TestAlgorithmsLib, try_is_looped) {
//    List<int> list;
//
//    for (int i = 0; i < 10; i++)
//        list.push_back(i * 3 + 1);
//
//    Node<int>* cur = list.tail();
//    cur->next = list.head()->next;
//    //std::cout << cur->data << std::endl;
//    /*for (auto it = list.begin(); it != list.end(); it++) {
//        std::cout << *it << " ";
//    }*/
//    EXPECT_TRUE(is_looped(&list));
//    cur->next = nullptr;
//}

TEST(TestAlgorithmsLib, try_is_looped_1) {
    List<int> list;

    for (int i = 0; i < 10; i++)
        list.push_back(i * 3 + 1);

    EXPECT_EQ(is_looped_rabbit_turtle(&list), false);
}

TEST(TestAlgorithmsLib, counting_of_islands) {
    Matrix<int> matr1(4, 4);
    matr1[0][0] = 0; matr1[0][1] = 1; matr1[0][2] = 0; matr1[0][3] = 0;
    matr1[1][0] = 0; matr1[1][1] = 0; matr1[1][2] = 0; matr1[1][3] = 0;
    matr1[2][0] = 1; matr1[2][1] = 0; matr1[2][2] = 1; matr1[2][3] = 1;
    matr1[3][0] = 1; matr1[3][1] = 0; matr1[3][2] = 1; matr1[3][3] = 0;

    int val = count_of_islands(matr1);
    EXPECT_TRUE(val == 3);
}